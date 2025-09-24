cmake_minimum_required(VERSION 4.1)

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

    GTest::gtest

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

# Testing
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

option(CRYPTONITE_BUILD_TESTS "Build the test suite" ON)
if(CRYPTONITE_BUILD_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()
