
include $(GNUSTEP_MAKEFILES)/common.make


LIBRARY_NAME = pHashAudio
pHashAudio_C_FILES = AudioHash.c kiss_fft.c kiss_fftr.c
pHashAudio_HEADER_FILES = AudioHash.h

TOOL_NAME = TestAudioHash
TestAudioHash_C_FILES = TestAudioHash.c
TestAudioHash_TOOL_LIBS = -lpHashAudio
TestAudioHash_LIB_DIRS = -L.
GNUSTEP_OBJ_DIR = .

-include GNUmakefile.preamble
include $(GNUSTEP_MAKEFILES)/library.make
include $(GNUSTEP_MAKEFILES)/tool.make
-include GNUmakefile.postamble
