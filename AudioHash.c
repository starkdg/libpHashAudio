#include "AudioHash.h"
#include <math.h>
#include <stdint.h>
#include "kiss_fftr.h"

#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#endif


static const unsigned int nfilts = 33;
static const float FreqWidth = 1.06f;

static const float Freqs[33] = {   50.0,  75.0,  100.0,  125.0,  150.0,   200.0,   250.0,   300.0, 
                                       350.0, 400.0,  450.0,  510.0,  570.0,   635.0,   700.0,   770.0, 
                                       840.0, 920.0, 1000.0, 1085.0, 1170.0,  1270.0,  1370.0,  1485.0, 
                                      1600.0,1725.0, 1850.0, 2000.0, 2150.0,  2325.0,  2500.0,  2700.0, 
                                      2900.0
                                     };

int getexpframelength(const int sr, const float dur){
    int count = 0, nbsamples = (int)(dur*(float)sr);
    while (nbsamples != 0){
	nbsamples >>= 1;
	count++;
    }
    count--;
    return count;
}

float* GetHammingWindow(const int length){
  float *window = (float*)malloc(length*sizeof(float));

  int i;
  for (i = 0;i < length;i++){
      window[i] = 0.54 - 0.46*cos(2*M_PI*i/(length-1));
  }

  return window;
}

float** GetWts(const int sr, const int nfft_half){
    float **wts = (float**)malloc(nfilts*sizeof(float*));
    int i, j;
    float maxfreq = (float)(sr/2);
    float f_bark_mid, mdouble, bark_diff, lof, hif;
    float *binbarks = (float*)malloc(nfft_half*sizeof(float));
    if (binbarks == NULL) return NULL;

    for (i=0; i < nfft_half;i++){
	/* frequency of point on axis */
	float temp = i*maxfreq/(float)nfft_half;

	/* asinh implentation freq => bark number conversion */
	/* approx of: bark = 6*arcsinh(freq/600)             */
	temp /= 600.0;
	binbarks[i] = 6*log(temp + sqrt(temp*temp + 1.0));
    }

    for (i=0;i < nfilts;i++){
      wts[i] = (float*)malloc(nfft_half*sizeof(float));
      if (wts[i] == NULL) return NULL;

      /*calculate wts for each filter */
      f_bark_mid = Freqs[i]/600.0;
      f_bark_mid = 6*log(f_bark_mid + sqrt(f_bark_mid*f_bark_mid + 1.0));
      for (j=0;j < nfft_half ;j++){
	  bark_diff = binbarks[j] - f_bark_mid;
	  lof = -2.5*(bark_diff/FreqWidth - 0.5);
	  hif = bark_diff/FreqWidth + 0.5;
	  mdouble = lof < hif ? lof : hif;
	  mdouble = (mdouble < 0) ? mdouble : 0; 
	  mdouble = pow(10,mdouble);
	  wts[i][j] = mdouble;
      }
    }

    free(binbarks);
    return wts;
}

void sort_barkdiffs(float *barkdiffs,unsigned char *bits,int length){
    int i, minpos;
    for (i=0;i<length;i++){
	minpos = i;
	int j;
	for (j=i+1;j<length;j++){
	    if (barkdiffs[j] < barkdiffs[minpos])
		minpos = j;
	}
	if (i != minpos){
	    float tmpdiff = barkdiffs[i];
	    barkdiffs[i] = barkdiffs[minpos];
	    barkdiffs[minpos] = tmpdiff;

	    unsigned char tmpbit = bits[i];
	    bits[i] = bits[minpos];
	    bits[minpos] = tmpbit;
	}
    }
}


int ph_audiohash(float *buf, int buflen, AudioHash *hash, AudioHashStInfo *st_info, int p, int sr){

    const float dur = 0.40f;
    int expcount, framelength, nfft_half;

    if (buf == NULL || buflen == 0 || hash == NULL || st_info == 0 || sr < 6000) return -1;

     if (st_info->framelength == 0){
	 expcount = getexpframelength(sr, dur);
	 framelength = 1 << expcount;
	 nfft_half = framelength/2;
	 st_info->framelength = framelength;
	 st_info->window = GetHammingWindow(framelength);
	 st_info->wts = GetWts(sr, framelength/2);
#ifdef __APPLE__
	 st_info->frame = (void*)malloc(framelength*sizeof(float));
	 st_info->pF = (float*)malloc(framelength*sizeof(float));
	 st_info->fft_context = (void*)vDSP_create_fftsetup(expcount, kFFTRadix2);
#else 
	 st_info->frame = (void*)calloc(framelength, sizeof(kiss_fft_scalar));
	 st_info->pF = (void*)calloc(framelength/2+1, sizeof(kiss_fft_cpx));
	 st_info->fft_context = (void*)kiss_fftr_alloc(framelength, 0, NULL, NULL);
#endif
	 st_info->magnF = (float*)malloc(nfft_half*sizeof(float));
	 st_info->freqdiffs = (float*)malloc((nfilts-1)*sizeof(float));
	 st_info->tmptoggles = (unsigned char*)malloc((nfilts-1)*sizeof(char));
     } else {
	 framelength = st_info->framelength;
	 nfft_half = framelength/2;
     }

    float *window = st_info->window;
    float **wts   = st_info->wts;


#ifdef __APPLE__
    float *pF =  (float*)st_info->pF;
    float *frame = (float*)st_info->frame;
    FFTSetup fftSeteupData = (FFTSetup)st_info->fft_context;
#else 
    kiss_fft_cpx *pF = (kiss_fft_cpx*)st_info->pF; 
    kiss_fft_scalar *frame = (kiss_fft_scalar*)st_info->frame;
    kiss_fftr_cfg kiss_cfg = (kiss_fftr_cfg)st_info->fft_context;
#endif

    float *magnF =  st_info->magnF;
    float *freqdiffs = st_info->freqdiffs;
    unsigned char *tmptoggles = st_info->tmptoggles;

    int start = 0;
    int end = start + framelength - 1;
    int overlap = 31*framelength/32;
    int advance = framelength - overlap;
    int totalframes = (int)(floor(buflen/advance) - floor(framelength/advance) + 1);
    int nbhashes = totalframes - 2;
    
    unsigned int *hasharray = (unsigned int*)malloc(nbhashes*sizeof(int));
    unsigned int *toggles = NULL;
    if (p > 0) toggles = (unsigned int*)malloc(nbhashes*sizeof(unsigned int));

    float **coeffs = (float**)malloc(totalframes*sizeof(float*));
    int i;
    for (i = 0;i < totalframes;i++){
	coeffs[i] = (float*)malloc(nfilts*sizeof(float));
    }

#ifdef __APPLE__
    DSPSplitComplex ioData;
    ioData.realp = pF;   
    ioData.imagp = pF + nfft_half;
#endif

    hash->hasharray = hasharray;
    hash->coeffs = coeffs;
    hash->toggles = toggles;
    hash->nbframes = totalframes;
    hash->nbhashes = nbhashes;
    hash->p = p;
    hash->nbcoeffs = nfilts-1;

    int index = 0,j;
    while (end < buflen){

#ifdef __APPLE__
	for (i = 0;i < framelength;i++){
	    frame[i] = window[i]*buf[start+i];
	}
	vDSP_ctoz((DSPComplex*)frame, 2, &ioData, 1, nfft_half);
	vDSP_fft_zrip(fftSetupData, &ioData, 1, expcount , kFFTDirection_Forward);
	vDSP_ztoc(&ioData, 1, (DSPComplex*)frame, 2, nfft_half);

	magnF[0] = frame[0];
	for (i=1;i<nfft_half-2;i++){
	    magnF[i] =  sqrt(pow(frame[2*i],2.0) + pow(frame[2*i+1], 2.0));
	}
	magnF[nfft_half-1] = frame[1];

#else 
	for (i=0;i<framelength;i++){
	    frame[i] = window[i]*buf[start+i];
	}
	kiss_fftr(kiss_cfg, frame, pF);

	for (i = 0;i < nfft_half;i++){   
	    magnF[i] = sqrt(pF[i].r*pF[i].r + pF[i].i*pF[i].i);
	}                                
#endif

	/* critical band integration */
	for (i = 0;i < nfilts;i++){
	    coeffs[index][i] = 0.0;
	    for (j = 0;j < nfft_half;j++){
		coeffs[index][i] += wts[i][j]*magnF[j];
	    }
	}
	index += 1;
	start += advance;
	end += advance;
    }

    index = 0;
    for (i = 1;i < totalframes - 1;i++){
	unsigned int hashvalue = 0;
	int m;
	for (m=0;m < nfilts-1;m++){
	    float diff = (coeffs[i+1][m] - coeffs[i+1][m+1]) - (coeffs[i-1][m] - coeffs[i-1][m+1]);
	    tmptoggles[m] = (unsigned char)m;
	    hashvalue <<= 1;
	    if (diff > 0){
		hashvalue |= 0x00000001;
	    }
	    freqdiffs[m] = floor(fabs(diff));
	}

	if (p > 0){
	    sort_barkdiffs(freqdiffs, tmptoggles, nfilts-1);
	    toggles[index] = 0;
	    for (m = 0;m < p;m++){
		toggles[index] |= (0x80000000 >> tmptoggles[m]);
	    }
	}
	hasharray[index++] = hashvalue;
    }

    return 0;
}

int ph_audiohash_wrapped(float *buf, int buflen, AudioHash *hash, int p, int sr){
    AudioHashStInfo st_info;
    ph_init_hashst(&st_info);
    int ret = ph_audiohash(buf, buflen, hash, &st_info, p, sr);
    ph_free_hashst(&st_info);
    return ret;
}

void ph_init_hashst(AudioHashStInfo *info){
    info->framelength = 0;
}

void ph_free_hashst(AudioHashStInfo *info){
    if (info != NULL){
	if (info->window) free(info->window);
	if (info->frame) free(info->frame);
	if (info->tmptoggles) free(info->tmptoggles);
	if (info->pF) free(info->pF);
	if (info->magnF) free(info->magnF);
	if (info->freqdiffs) free(info->freqdiffs);
#ifdef __APPLE__
	vDSP_destroy_fftsetup(FFTSetup)info->fft_context);
#else 
	if (info->fft_context) kiss_fftr_free(info->fft_context);
#endif
	int i;
	if (info->wts){
	    for (i=0;i < nfilts;i++){
		if (info->wts[i]) free(info->wts[i]);
	    }
	    free(info->wts);
	}
    }

}

void ph_free_hash(AudioHash *hash){
    if (hash != NULL){
	if (hash->hasharray) free(hash->hasharray);
	int i;
	if (hash->coeffs){
	    for (i=0;i<hash->nbframes;i++){
		free(hash->coeffs[i]);
	    }
	    free(hash->coeffs);
	}
	if (hash->toggles) free(hash->toggles);
    }
}

int ph_bitcount(unsigned int n){
     int count = 0;
    while (n != 0) {
	n >>= 1;
	count++;
    }
    return count;
}

/** auxiliary function to distance_ber
 **/
float ph_compare_blocks(unsigned int *ptr_blockA, unsigned int *toggles,
                         unsigned int  *ptr_blockB,
			int length){
    float result = 0;
    int i;
    for (i=0;i < length;i++){
	unsigned int bitmask = (toggles != NULL) ? toggles[i] : 0;
	unsigned int xordhash = (ptr_blockA[i]^ptr_blockB[i]) & (~bitmask);
	result += (double)ph_bitcount(xordhash);
    }
    result /= (double)(32*length);
    return result;
}

float ph_get_offset_secs(int sr, int position){
    int expcount = getexpframelength(sr, 0.40f);
    int fl = 1 << expcount;
    return (float)(fl*position)/(float)(32*sr);
}

int ph_audiohash_distance_ber(AudioHash *hasha, AudioHash *hashb, int *pos, float *cs){
    if (hasha == NULL || hashb == NULL) return -1;
    
    int Na = hasha->nbhashes;
    int Nb = hashb->nbhashes;
    if (Na > Nb) return -1; // (Nb >= Na) always!

    int Nc = Nb - Na + 1;

    *pos = -1;
    *cs  = 0.0f;

    uint32_t *pha,*phb, *togs = NULL;
    float dist;

    if (hasha->toggles != NULL) {
	togs = hasha->toggles;
    }

    int i;
    for (i=0; i < Nc;i++){

        pha = hasha->hasharray;
        phb = hashb->hasharray + i;
	if (togs != NULL) togs = hasha->toggles;

	pha = hasha->hasharray;
	phb = hashb->hasharray + i;

	dist = 1 - ph_compare_blocks(pha,togs,phb,Na);
	if (dist > *cs){
	    *cs = dist;
	    *pos = i;
	}
    }
    return 0;
}

