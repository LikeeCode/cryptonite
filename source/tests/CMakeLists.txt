add_executable(TestBinanceAPI
    api/binance/TestBinanceAPI.cpp
)

target_include_directories(TestBinanceAPI PUBLIC ${CMAKE_SOURCE_DIR}/api/binance/include/)

target_link_libraries(TestBinanceAPI PRIVATE
    Qt6::Core
    Qt6::Network

    BinanceAPI
)

add_test(NAME "BinanceAPI" COMMAND TestBinanceAPI)
