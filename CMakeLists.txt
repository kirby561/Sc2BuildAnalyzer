cmake_minimum_required(VERSION 2.8.12)

project(Sc2BuildAnalyzer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(SbaCore)
add_subdirectory(SbaUi)

# Copy QT binaries
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/SbaUi/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/SbaUi/Release)
add_custom_target(Qt5CopyBinaries
  # debug version
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGLd.dll          ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2d.dll       ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll         ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll          ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Networkd.dll      ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGLd.dll       ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Scriptd.dll       ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sqld.dll          ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll      ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xmld.dll          ${CMAKE_BINARY_DIR}/SbaUi/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatternsd.dll  ${CMAKE_BINARY_DIR}/SbaUi/Debug
  
  # release version
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGL.dll           ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2.dll        ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll          ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll           ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Network.dll       ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll        ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Script.dll        ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sql.dll           ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xml.dll           ${CMAKE_BINARY_DIR}/SbaUi/Release
  COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatterns.dll   ${CMAKE_BINARY_DIR}/SbaUi/Release

  # Output Message
  COMMENT "Copying Qt binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
)

add_dependencies(SbaCore Qt5CopyBinaries)
