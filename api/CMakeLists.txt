add_library(APICommon INTERFACE)

target_include_directories(APICommon INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(binance)
