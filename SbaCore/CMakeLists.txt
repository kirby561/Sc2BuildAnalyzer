
include_directories("Source"
					"Source/Utility")
			
add_library(SbaCore STATIC
				"Source/ReplayData/ReplayData.h"
				"Source/ReplayData/Sc2UnitEvent.h"
				"Source/ReplayData/Sc2EventIds.h"
				"Source/ReplayData/Sc2EventIds.cpp"
				"Source/ReplayData/Sc2Player.h"
				"Source/ReplayData/Sc2Replay.h"
				"Source/ReplayParser.h"
				"Source/ReplayData/Sc2Unit.h"
				"Source/ReplayData/Sc2Unit.cpp"
				"Source/ReplayData/Sc2UnitEvent.cpp"
				"Source/ReplayParser.cpp"
				"Source/Build.h"
				"Source/Build.cpp"
				"Source/Project.h"
				"Source/Project.cpp"
				"Source/Filter.h"
				"Source/Filter.cpp"
				"Source/BuildComparator.h"
				"Source/BuildComparator.cpp"
				"Source/Utility/Log.h"
				"Source/Utility/Log.cpp"
				"Source/Utility/Property.h"
				"Source/Utility/DataObject.h"
				"Source/Utility/DataObject.cpp"
				"Source/Utility/ArrayProperty.h"
				"Source/Utility/UtilityTester.h"
				"Source/Utility/UtilityTester.cpp"
				"Source/Utility/ProgressListener.h"
				"Source/Utility/WorkQueueThread.h"
				"Source/Utility/WorkQueueThread.cpp")

target_link_libraries(SbaCore Qt5::Core)
