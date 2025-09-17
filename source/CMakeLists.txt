# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name and language
project(Cryptonite LANGUAGES CXX RC)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# These are crucial for Qt projects. They tell CMake to automatically run
# Qt's tools (moc, rcc, uic) when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the Qt6 package. We need the "Quick" module for QML.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network)

# Define the executable target.
# It's built from main.cpp and includes the resources from main.qrc.
add_executable(Cryptonite
  main.cpp
  main.qrc
  icon.rc
)

# Link the executable against the Qt6::Quick library
target_link_libraries(Cryptonite PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Network
)

# windeployqt is a tool provided by Qt to help deploy applications on Windows.
# It copies the necessary Qt DLLs and plugins to the output directory.
if(WIN32 AND WINDEPLOYQT_EXECUTABLE)
    # Add a custom command that runs AFTER the Cryptonite target is built.
    add_custom_command(
        TARGET Cryptonite
        POST_BUILD
        # The command and its arguments
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
            --qmldir "${CMAKE_CURRENT_SOURCE_DIR}"
            --pdb
            "$<TARGET_FILE:Cryptonite>"
        # A message to print during the build
        COMMENT "Running windeployqt to deploy Qt DLLs..."
        # This is the crucial addition!
        VERBATIM
    )
endif()
