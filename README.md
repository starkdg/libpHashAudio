##	libpHashAudio v1.0.0

Project produces two executables:

  - libpHashAudio: contains audio hash function.
    (Code is in Audiohash.c/AudioHash.h)
  
  - TestAudioHash: test executable.  
    It uses the samples in sample.txt file to run the test.

### Notes for dev on Apple OS

Compilation depends on the GNUStep dev framework which is 
a rough parallel to mac's NextStep development framework.
Change the Makefile variables as needed.

NOTE: Look at making the following changes to for on mac ios.

AudioHash.c:line 2 -> change include to proper header for native fft implementation
		      (Will not need the JFFT.h/.c and JComplex.h/.c files).

AudioHash.c:line 163 -> change fft function call to proper function.
		        variables: frame - is the double array containing samples to transform.
                                   pF    - is the JComplex array containing the sample.

AudioHash.c:line 165 -> calculate absolute values from complex numbers of pF[] and put them in
                        magnf[] double array.  The ios function is in-place, so you probably won't 
                        even need the pF buffer.  Just use the frame buffer (enlarge its allocation
                        on line 114 as needed.

links to developer documentation:

[apple dev](https://developer.apple.com/library/ios/#documentation/Accelerate/Reference/vDSPRef/Reference/reference.html#//apple_ref/doc/uid/TP40009464)


