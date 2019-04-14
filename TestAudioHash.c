#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "AudioHash.h"

void runtest(){
    const char *file = "sample.txt";
    const int sr = 6000;
    const int p = 12;
    
    FILE *samplefile = fopen(file, "r");
    assert(samplefile != NULL);

    int i, buflen;
    fscanf(samplefile, "%d", &buflen);
    
    float *buf = malloc(buflen*sizeof(float));
    assert(buf != NULL);

    for (i=0;i<buflen;i++){
	fscanf(samplefile, "%f", buf+i);
    }
    fclose(samplefile);

    AudioHash hash;
    int ret = ph_audiohash_wrapped(buf, buflen, &hash, p, sr);
    assert(ret == 0);

    assert(hash.nbhashes == 33);
    assert(hash.nbframes == 35);
    assert(hash.nbcoeffs == 32);

    assert(hash.hasharray[0] == 0xcb0f9ef0);
    assert(hash.hasharray[1] == 0xcb0fbaf0);
    assert(hash.hasharray[2] == 0xcb0eb870);
    assert(hash.hasharray[3] == 0xcb0ef870);
    assert(hash.hasharray[30] == 0xf0b86b00);
    assert(hash.hasharray[31] == 0xf0b86901);
    assert(hash.hasharray[32] == 0xf0b8780b);

    assert(hash.toggles[0] == 0x6889fc00);
    assert(hash.toggles[1] == 0x6889fc00);
    assert(hash.toggles[2] == 0x6889db00);
    assert(hash.toggles[3] == 0x3889d980);
    assert(hash.toggles[30] == 0x21c8fe00);
    assert(hash.toggles[31] == 0x9c8f700);
    assert(hash.toggles[32] == 0x8c8ff00);


    AudioHash subhash;
    ret = ph_audiohash_wrapped(buf+500, buflen-500, &subhash, p, sr);
    assert(ret == 0);

    int pos;
    float cs;
    ret = ph_audiohash_distance_ber(&subhash, &hash, &pos, &cs);
    assert(ret == 0);
    printf("pos %d, cs %f\n", pos, cs);

    free(buf);
    ph_free_hash(&hash);
    ph_free_hash(&subhash);
}

int main(int argc, char **argv){

    printf("1 run test.\n");
    runtest();

    return 0;
}
