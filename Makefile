# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/projects/libpHashAudio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/projects/libpHashAudio

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/david/projects/libpHashAudio/CMakeFiles /home/david/projects/libpHashAudio/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/david/projects/libpHashAudio/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named TestpHashAudio

# Build rule for target.
TestpHashAudio: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TestpHashAudio
.PHONY : TestpHashAudio

# fast build rule for target.
TestpHashAudio/fast:
	$(MAKE) -f CMakeFiles/TestpHashAudio.dir/build.make CMakeFiles/TestpHashAudio.dir/build
.PHONY : TestpHashAudio/fast

#=============================================================================
# Target rules for targets named pHashAudio

# Build rule for target.
pHashAudio: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pHashAudio
.PHONY : pHashAudio

# fast build rule for target.
pHashAudio/fast:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/build
.PHONY : pHashAudio/fast

AudioHash.o: AudioHash.c.o

.PHONY : AudioHash.o

# target to build an object file
AudioHash.c.o:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/AudioHash.c.o
.PHONY : AudioHash.c.o

AudioHash.i: AudioHash.c.i

.PHONY : AudioHash.i

# target to preprocess a source file
AudioHash.c.i:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/AudioHash.c.i
.PHONY : AudioHash.c.i

AudioHash.s: AudioHash.c.s

.PHONY : AudioHash.s

# target to generate assembly for a file
AudioHash.c.s:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/AudioHash.c.s
.PHONY : AudioHash.c.s

TestAudioHash.o: TestAudioHash.c.o

.PHONY : TestAudioHash.o

# target to build an object file
TestAudioHash.c.o:
	$(MAKE) -f CMakeFiles/TestpHashAudio.dir/build.make CMakeFiles/TestpHashAudio.dir/TestAudioHash.c.o
.PHONY : TestAudioHash.c.o

TestAudioHash.i: TestAudioHash.c.i

.PHONY : TestAudioHash.i

# target to preprocess a source file
TestAudioHash.c.i:
	$(MAKE) -f CMakeFiles/TestpHashAudio.dir/build.make CMakeFiles/TestpHashAudio.dir/TestAudioHash.c.i
.PHONY : TestAudioHash.c.i

TestAudioHash.s: TestAudioHash.c.s

.PHONY : TestAudioHash.s

# target to generate assembly for a file
TestAudioHash.c.s:
	$(MAKE) -f CMakeFiles/TestpHashAudio.dir/build.make CMakeFiles/TestpHashAudio.dir/TestAudioHash.c.s
.PHONY : TestAudioHash.c.s

kiss_fft.o: kiss_fft.c.o

.PHONY : kiss_fft.o

# target to build an object file
kiss_fft.c.o:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fft.c.o
.PHONY : kiss_fft.c.o

kiss_fft.i: kiss_fft.c.i

.PHONY : kiss_fft.i

# target to preprocess a source file
kiss_fft.c.i:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fft.c.i
.PHONY : kiss_fft.c.i

kiss_fft.s: kiss_fft.c.s

.PHONY : kiss_fft.s

# target to generate assembly for a file
kiss_fft.c.s:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fft.c.s
.PHONY : kiss_fft.c.s

kiss_fftr.o: kiss_fftr.c.o

.PHONY : kiss_fftr.o

# target to build an object file
kiss_fftr.c.o:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fftr.c.o
.PHONY : kiss_fftr.c.o

kiss_fftr.i: kiss_fftr.c.i

.PHONY : kiss_fftr.i

# target to preprocess a source file
kiss_fftr.c.i:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fftr.c.i
.PHONY : kiss_fftr.c.i

kiss_fftr.s: kiss_fftr.c.s

.PHONY : kiss_fftr.s

# target to generate assembly for a file
kiss_fftr.c.s:
	$(MAKE) -f CMakeFiles/pHashAudio.dir/build.make CMakeFiles/pHashAudio.dir/kiss_fftr.c.s
.PHONY : kiss_fftr.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install"
	@echo "... TestpHashAudio"
	@echo "... rebuild_cache"
	@echo "... pHashAudio"
	@echo "... install/local"
	@echo "... test"
	@echo "... list_install_components"
	@echo "... edit_cache"
	@echo "... AudioHash.o"
	@echo "... AudioHash.i"
	@echo "... AudioHash.s"
	@echo "... TestAudioHash.o"
	@echo "... TestAudioHash.i"
	@echo "... TestAudioHash.s"
	@echo "... kiss_fft.o"
	@echo "... kiss_fft.i"
	@echo "... kiss_fft.s"
	@echo "... kiss_fftr.o"
	@echo "... kiss_fftr.i"
	@echo "... kiss_fftr.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

