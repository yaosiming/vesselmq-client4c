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
include example/simple/CMakeFiles/push_consumer.dir/depend.make

# Include the progress variables for this target.
include example/simple/CMakeFiles/push_consumer.dir/progress.make

# Include the compile flags for this target's objects.
include example/simple/CMakeFiles/push_consumer.dir/flags.make

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o: example/simple/CMakeFiles/push_consumer.dir/flags.make
example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o: ../example/simple/PushConsumer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yaosir/space/vesselmq-client4c/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/push_consumer.dir/PushConsumer.cpp.o -c /home/yaosir/space/vesselmq-client4c/example/simple/PushConsumer.cpp

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/push_consumer.dir/PushConsumer.cpp.i"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yaosir/space/vesselmq-client4c/example/simple/PushConsumer.cpp > CMakeFiles/push_consumer.dir/PushConsumer.cpp.i

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/push_consumer.dir/PushConsumer.cpp.s"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yaosir/space/vesselmq-client4c/example/simple/PushConsumer.cpp -o CMakeFiles/push_consumer.dir/PushConsumer.cpp.s

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.requires:
.PHONY : example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.requires

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.provides: example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.requires
	$(MAKE) -f example/simple/CMakeFiles/push_consumer.dir/build.make example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.provides.build
.PHONY : example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.provides

example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.provides.build: example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o

# Object files for target push_consumer
push_consumer_OBJECTS = \
"CMakeFiles/push_consumer.dir/PushConsumer.cpp.o"

# External object files for target push_consumer
push_consumer_EXTERNAL_OBJECTS =

example/simple/push_consumer: example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o
example/simple/push_consumer: example/simple/CMakeFiles/push_consumer.dir/build.make
example/simple/push_consumer: librocketmq.so
example/simple/push_consumer: libs/jsoncpp-src-0.5.0/lib/libjsoncpp.so
example/simple/push_consumer: example/simple/CMakeFiles/push_consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable push_consumer"
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/push_consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/simple/CMakeFiles/push_consumer.dir/build: example/simple/push_consumer
.PHONY : example/simple/CMakeFiles/push_consumer.dir/build

example/simple/CMakeFiles/push_consumer.dir/requires: example/simple/CMakeFiles/push_consumer.dir/PushConsumer.cpp.o.requires
.PHONY : example/simple/CMakeFiles/push_consumer.dir/requires

example/simple/CMakeFiles/push_consumer.dir/clean:
	cd /home/yaosir/space/vesselmq-client4c/build/example/simple && $(CMAKE_COMMAND) -P CMakeFiles/push_consumer.dir/cmake_clean.cmake
.PHONY : example/simple/CMakeFiles/push_consumer.dir/clean

example/simple/CMakeFiles/push_consumer.dir/depend:
	cd /home/yaosir/space/vesselmq-client4c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yaosir/space/vesselmq-client4c /home/yaosir/space/vesselmq-client4c/example/simple /home/yaosir/space/vesselmq-client4c/build /home/yaosir/space/vesselmq-client4c/build/example/simple /home/yaosir/space/vesselmq-client4c/build/example/simple/CMakeFiles/push_consumer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/simple/CMakeFiles/push_consumer.dir/depend

