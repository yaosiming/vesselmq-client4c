# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build

# Include any dependencies generated for this target.
include CMakeFiles/jsoncpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jsoncpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsoncpp.dir/flags.make

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o: ../src/lib_json/json_reader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o -c /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_reader.cpp

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_reader.cpp > CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.i

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_reader.cpp -o CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.s

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.requires:
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.requires

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.provides: CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.requires
	$(MAKE) -f CMakeFiles/jsoncpp.dir/build.make CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.provides.build
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.provides

CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.provides.build: CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o: ../src/lib_json/json_value.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o -c /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_value.cpp

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_value.cpp > CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.i

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_value.cpp -o CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.s

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.requires:
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.requires

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.provides: CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.requires
	$(MAKE) -f CMakeFiles/jsoncpp.dir/build.make CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.provides.build
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.provides

CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.provides.build: CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o: ../src/lib_json/json_writer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o -c /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_writer.cpp

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_writer.cpp > CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.i

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/src/lib_json/json_writer.cpp -o CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.s

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.requires:
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.requires

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.provides: CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.requires
	$(MAKE) -f CMakeFiles/jsoncpp.dir/build.make CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.provides.build
.PHONY : CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.provides

CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.provides.build: CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o

# Object files for target jsoncpp
jsoncpp_OBJECTS = \
"CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o" \
"CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o" \
"CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o"

# External object files for target jsoncpp
jsoncpp_EXTERNAL_OBJECTS =

lib/libjsoncpp.so: CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o
lib/libjsoncpp.so: CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o
lib/libjsoncpp.so: CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o
lib/libjsoncpp.so: CMakeFiles/jsoncpp.dir/build.make
lib/libjsoncpp.so: CMakeFiles/jsoncpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library lib/libjsoncpp.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsoncpp.dir/build: lib/libjsoncpp.so
.PHONY : CMakeFiles/jsoncpp.dir/build

CMakeFiles/jsoncpp.dir/requires: CMakeFiles/jsoncpp.dir/src/lib_json/json_reader.cpp.o.requires
CMakeFiles/jsoncpp.dir/requires: CMakeFiles/jsoncpp.dir/src/lib_json/json_value.cpp.o.requires
CMakeFiles/jsoncpp.dir/requires: CMakeFiles/jsoncpp.dir/src/lib_json/json_writer.cpp.o.requires
.PHONY : CMakeFiles/jsoncpp.dir/requires

CMakeFiles/jsoncpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jsoncpp.dir/clean

CMakeFiles/jsoncpp.dir/depend:
	cd /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0 /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0 /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build /home/yaosir/space/vesselmq-client4c/libs/jsoncpp-src-0.5.0/build/CMakeFiles/jsoncpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsoncpp.dir/depend

