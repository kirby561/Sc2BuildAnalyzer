
include_directories("Source"
					"Source/Utility"
					"Dependencies/Python27/Include")

find_library(Python27 "python27" PATHS "Dependencies/Python27/Lib")
find_library(Python27d "python27_d" PATHS "Dependencies/Python27/Lib")
					
add_library(SbaCore STATIC
				"Source/ReplayParser.cpp"
				"Source/Utility/Log.cpp")

target_link_libraries(SbaCore Qt5::Core)

# For some reason python wants a python27_d.lib to exist even though it doesn't ship with one.
#    I fixed this by just copy/pasting the release one and renaming it.
target_link_libraries(SbaCore debug ${Python27d} optimized ${Python27})
