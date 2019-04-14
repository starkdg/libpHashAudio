#ifndef _AUDIO_HASH_H
#define _AUDIO_HASH_H

#if defined(BUILD_DLL)
#define PHASHAUDIO_EXPORT __declspec(dllexport)
#elif defined(BUILD_EXE)
#define PHASHAUDIO_EXPORT __declspec(dllimport)
#else
#define PHASHAUDIO_EXPORT
#endif

typedef struct hash_state {
    float *window;          /* internal state information for hash function */
    float **wts;
    void *frame;
    unsigned char *tmptoggles;
    void *pF;
    float *magnF;
    float *freqdiffs;
    int framelength;
    void *fft_context;
} AudioHashStInfo;

typedef struct audiohash {
    float **coeffs; /* float[][] 2d array of size (nbframes+2)*nbcoeffs */
    unsigned int *toggles; /* int array of length nbframes  */
    unsigned int *hasharray; /* int array of length nbframes */
    int nbframes;
    int nbhashes;
    int p;
    int nbcoeffs;
} AudioHash;

/** calculate audio hash for signal
 *  @param buf buffer of float sample data
 *  @param buflen length of audio buffer
 *  @param hash ptr to AudioHash struct
 *  @param st_info ptr to state info (call inithashst() before first call)
 *  @param p int value for no. toggles
 *  @param sr sampling rate (e.g. 6000)
 *  @return int 0 
 **/
PHASHAUDIO_EXPORT
int ph_audiohash(float *buf, int buflen, AudioHash *hash, AudioHashStInfo *st_info, int p, int sr);

/** calculate audiohash for signal
 *  convenience method to calculate audiohash without init/free'ing state info
 *  @param buf signal buffer
 *  @param buflen length of buf
 *  @param hash   AudioHash struct
 *  @param p     int value for no. toggles (permutations) to consider for each hash
 *  @param sr    sample rate for the signal buffer
 *  @return 0 for success, neg for 0.
 *
 **/
PHASHAUDIO_EXPORT
int ph_audiohash_wrapped(float *buf, int buflen, AudioHash *hash, int p, int sr);

/* init hash struct (set framelength to 0 
 * @param info 
 * @return void
 */
PHASHAUDIO_EXPORT
void ph_init_hashst(AudioHashStInfo *info);

/** free data in AudioHashStInfo struct 
 * @param info
 * @return void
 **/
PHASHAUDIO_EXPORT
void ph_free_hashst(AudioHashStInfo *info);

/** free AudioHash returned struct 
 *  @param hash
 *  @return void 
 **/
PHASHAUDIO_EXPORT
void ph_free_hash(AudioHash *hash);


/** returns no. of seconds  at position for given samplerate
 *  @param sr samplerate
 *  @param position int index position
 *  @return float value for no. seconds.
 **/
PHASHAUDIO_EXPORT
float ph_get_offset_secs(int sr, int position);


/** compressed version of distance function
    @param hasha - the first (shorter) audio hash
    @param hashb - the second (longer) audio hash
    @param pos position in second hash in which first hash is found [out]
    @param cs  confidence score of this match, 0-1.0 [out]
    @return 0 on success, negative on error
 **/
PHASHAUDIO_EXPORT
int ph_audiohash_distance_ber(AudioHash *hasha, AudioHash *hashb, int *pos, float *cs);


#endif /* AudioHash_H */
