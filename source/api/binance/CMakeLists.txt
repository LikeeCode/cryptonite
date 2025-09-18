# Collect all header and source files in this directory
file(GLOB BINANCE_API_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(BinanceAPI STATIC ${BINANCE_API_SOURCES})

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE Qt6::Core)
