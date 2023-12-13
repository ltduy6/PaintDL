cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(PaintApp_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# hack for buggy CMake's FindwxWidgets script
if(DEFINED ENV_WX_CONFIG)
    set(ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets REQUIRED xml core base)

set(SRCS 
# Main folder
main.cpp 
DrawingView.cpp 
DrawingDocument.cpp
# Canvas folder
Canvas/DrawingCanvas.cpp 
Canvas/CanvasObject.cpp
Canvas/ObjectSpace.cpp
Canvas/SelectionBox.cpp
Canvas/ShapeCreator.cpp
# Gradient
Gradient/gradient.cpp
Gradient/gradientdlg.cpp
Gradient/GradientBrush.cpp
# Menu folder
Menu/SelectablePane.cpp 
Menu/ColorPane.cpp 
Menu/SizePane.cpp 
Menu/ShapePane.cpp
Menu/ToolsPane.cpp
Menu/ColorMenu.cpp
Menu/SizeMenu.cpp
Menu/ShapeMenu.cpp
Menu/ToolMenu.cpp
Menu/ImageMenu.cpp
Menu/HistoryPanel.cpp
Menu/HistoryPane.cpp
Menu/MenuTemplate.cpp
Menu/BrushToolMenu.cpp
Menu/MenuBar.cpp
Menu/ShapeToolMenu.cpp
Menu/SelectionToolMenu.cpp
Menu/TextToolMenu.cpp
Menu/ZoomToolMenu.cpp
Menu/ZoomMenu.cpp
Menu/MoveToolMenu.cpp
Menu/FontMenu.cpp
# Command folder
Command/AddCommand.cpp
Command/SelectionCommand.cpp
Command/ShapeCommand.cpp)

include(${wxWidgets_USE_FILE})

if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(main WIN32 ${SRCS} main.exe.manifest)

endif()

target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})