# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/yaosir/space/vesselmq-client4c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yaosir/space/vesselmq-client4c/build

# Include any dependencies generated for this target.
include example/simple/CMakeFiles/producer.dir/depend.make

# Include the progress variables for this target.
include example/simple/CMakeFiles/producer.dir/progress.make

# Include the compile flags for this target's objects.
include example/simple/CMakeFiles/producer.dir/flags.make

example/simple/CMakeFiles/producer.dir/Producer.cpp.o: example/simple/CMakeFiles/producer.dir/flags.make
example/simple/CMakeFiles/producer.dir/Producer.cpp.o: ../example/simple/Producer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yaosir/space/vesselmq-client4c/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object example/simple/CMakeFiles/producer.dir/Producer.cpp.o"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/producer.dir/Producer.cpp.o -c /home/yaosir/space/vesselmq-client4c/example/simple/Producer.cpp

example/simple/CMakeFiles/producer.dir/Producer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/producer.dir/Producer.cpp.i"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yaosir/space/vesselmq-client4c/example/simple/Producer.cpp > CMakeFiles/producer.dir/Producer.cpp.i

example/simple/CMakeFiles/producer.dir/Producer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/producer.dir/Producer.cpp.s"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yaosir/space/vesselmq-client4c/example/simple/Producer.cpp -o CMakeFiles/producer.dir/Producer.cpp.s

example/simple/CMakeFiles/producer.dir/Producer.cpp.o.requires:
.PHONY : example/simple/CMakeFiles/producer.dir/Producer.cpp.o.requires

example/simple/CMakeFiles/producer.dir/Producer.cpp.o.provides: example/simple/CMakeFiles/producer.dir/Producer.cpp.o.requires
	$(MAKE) -f example/simple/CMakeFiles/producer.dir/build.make example/simple/CMakeFiles/producer.dir/Producer.cpp.o.provides.build
.PHONY : example/simple/CMakeFiles/producer.dir/Producer.cpp.o.provides

example/simple/CMakeFiles/producer.dir/Producer.cpp.o.provides.build: example/simple/CMakeFiles/producer.dir/Producer.cpp.o

# Object files for target producer
producer_OBJECTS = \
"CMakeFiles/producer.dir/Producer.cpp.o"

# External object files for target producer
producer_EXTERNAL_OBJECTS =

example/simple/producer: example/simple/CMakeFiles/producer.dir/Producer.cpp.o
example/simple/producer: example/simple/CMakeFiles/producer.dir/build.make
example/simple/producer: librocketmq.so
example/simple/producer: libs/jsoncpp-src-0.5.0/lib/libjsoncpp.so
example/simple/producer: example/simple/CMakeFiles/producer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable producer"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/producer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/simple/CMakeFiles/producer.dir/build: example/simple/producer
.PHONY : example/simple/CMakeFiles/producer.dir/build

example/simple/CMakeFiles/producer.dir/requires: example/simple/CMakeFiles/producer.dir/Producer.cpp.o.requires
.PHONY : example/simple/CMakeFiles/producer.dir/requires

example/simple/CMakeFiles/producer.dir/clean:
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && $(CMAKE_COMMAND) -P CMakeFiles/producer.dir/cmake_clean.cmake
.PHONY : example/simple/CMakeFiles/producer.dir/clean

example/simple/CMakeFiles/producer.dir/depend:
	cd /home/yaosir/space/vesselmq-client4c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yaosir/space/vesselmq-client4c /home/yaosir/space/vesselmq-client4c/example/simple /home/yaosir/space/vesselmq-client4c/build /home/yaosir/space/vesselmq-client4c/build/example/simple /home/yaosir/space/vesselmq-client4c/build/example/simple/CMakeFiles/producer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/simple/CMakeFiles/producer.dir/depend

