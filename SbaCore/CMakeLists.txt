
include_directories("Source"
					"Source/Utility")
			
add_library(SbaCore STATIC
				"Source/ReplayData/ReplayData.h"
				"Source/ReplayData/Sc2CreationEvent.h"
				"Source/ReplayData/Sc2EventIds.h"
				"Source/ReplayData/Sc2Player.h"
				"Source/ReplayData/Sc2Replay.h"
				"Source/ReplayParser.h"
				"Source/ReplayData/Sc2Unit.h"
				"Source/ReplayData/Sc2Unit.cpp"
				"Source/ReplayParser.cpp"
				"Source/Utility/Log.h"
				"Source/Utility/Log.cpp")

target_link_libraries(SbaCore Qt5::Core)
