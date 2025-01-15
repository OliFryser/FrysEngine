# CMakeList.txt : CMake project for FrysEngine, include source and define
# project specific logic here.

# Add source to this project's executable.
file(GLOB_RECURSE ExampleGame-src "*.cpp")
#file(GLOB_RECURSE ExampleGame-hpp "*.h")
add_executable (ExampleGame ${ExampleGame-src})

# Link to the actual SDL3 library.
target_link_libraries(ExampleGame PRIVATE SDL3::SDL3)
target_link_libraries(ExampleGame PRIVATE FrysEngineLibrary)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ExampleGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
