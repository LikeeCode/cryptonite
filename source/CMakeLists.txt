cmake_minimum_required(VERSION 3.14)

# Define the project name and languages
project(Cryptonite LANGUAGES CXX RC)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# These are crucial for Qt projects. They tell CMake to automatically run
# Qt's tools (moc, rcc, uic) when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the Qt6 and its components
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network)

# Include all subdirectories
add_subdirectory(api)

# Set a common output directory for all executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

# Define the main executable
add_executable(Cryptonite
  main.cpp
  main.qrc
  icon.rc
)

# Link the main executable
target_link_libraries(Cryptonite PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Network

    BinanceAPI
)

# Define post-build function for the deployment
function(deploy_qt_target TARGET_NAME)
    if(WIN32 AND WINDEPLOYQT_EXECUTABLE)
        add_custom_command(
            TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE}
                --qmldir "${CMAKE_CURRENT_SOURCE_DIR}"
                --pdb
                "$<TARGET_FILE:${TARGET_NAME}>"
            COMMENT "Running windeployqt to deploy Qt DLLs for ${TARGET_NAME}..."
        )
    endif()
endfunction()

# Use post-build function for the deployment
deploy_qt_target(Cryptonite)

# This command runs after Cryptonite is built and copies the API key file
# to the same directory as the executable.
add_custom_command(
    TARGET Cryptonite POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/apiKeys/binanceAPI.txt"
        # This generator expression correctly resolves to the output directory at build time
        "$<TARGET_FILE_DIR:Cryptonite>/apiKeys/binanceAPI.txt"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Cryptonite>/apiKeys" # Create dir if not exists
    COMMENT "Copying API key file for Cryptonite executable..."
)

# Testing
include(CTest)
enable_testing()
add_subdirectory(3rdParty/googletest)
add_subdirectory(tests)
set_target_properties(gtest gtest_main gmock gmock_main
    PROPERTIES FOLDER 3rdParty/googletest)
