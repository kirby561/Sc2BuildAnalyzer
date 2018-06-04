
include_directories("Source"
					"Source/Utility")
			
add_library(SbaCore STATIC
				"Source/ReplayParser.cpp"
				"Source/Utility/Log.cpp")

target_link_libraries(SbaCore Qt5::Core)
