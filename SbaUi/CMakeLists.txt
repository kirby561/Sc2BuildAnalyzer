
include_directories("."
					"../SbaCore/Source"
					"../SbaCore/Source/Utility")

add_executable(SbaUi
				"Main.cpp"
				"Resources.h"
				"Resources.cpp"
				"WindowManager.h"
				"WindowManager.cpp"
				"StartScreen.h"
				"StartScreen.cpp"
				"StartScreen.ui"
				"ProjectWindow.h"
				"ProjectWindow.cpp"
				"ProjectWindow.ui")

target_link_libraries(SbaUi SbaCore Qt5::Core Qt5::Widgets)