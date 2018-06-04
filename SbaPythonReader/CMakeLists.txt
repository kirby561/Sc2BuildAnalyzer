
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SbaUi)
include_directories("Source"
					"Dependencies/Python27/Include")

find_library(Python27 "python27" PATHS "Dependencies/Python27/Lib")
find_library(Python27d "python27_d" PATHS "Dependencies/Python27/Lib")
					
add_executable(SbaPythonReader
				"Source/Main.cpp"
				"Source/ReplayReader.cpp")

target_link_libraries(SbaPythonReader Qt5::Core)

# For some reason python wants a python27_d.lib to exist even though it doesn't ship with one.
#    I fixed this by just copy/pasting the release one and renaming it.
target_link_libraries(SbaPythonReader debug ${Python27d} optimized ${Python27})
