file(GLOB_RECURSE FrysEngineLibrary-src "*.cpp")
file(GLOB_RECURSE FrysEngineLibrary-hpp "*.h")

add_library(FrysEngineLibrary ${FrysEngineLibrary-src} ${FrysEngineLibrary-hpp})
target_link_libraries(FrysEngineLibrary PRIVATE SDL3::SDL3)