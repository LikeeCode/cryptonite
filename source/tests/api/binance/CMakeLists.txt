add_executable(BinanceAPITest
    BinanceAPITest.cpp
)

target_include_directories(BinanceAPITest PRIVATE
    3rdprty/googletest/include
    ${CMAKE_SOURCE_DIR}/api/binance/include/
)

target_link_libraries(BinanceAPITest PRIVATE
    Qt6::Core
    Qt6::Network

    GTest::gtest

    BinanceAPI
)

add_test(NAME BinanceAPITest COMMAND BinanceAPITest)

deploy_qt_target(BinanceAPITest)
