# Binance API GeneralDataParserTest
add_executable(GeneralDataParserTest
    GeneralDataParserTest.cpp
)

set_target_properties(GeneralDataParserTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

target_include_directories(GeneralDataParserTest PRIVATE
    ${CMAKE_SOURCE_DIR}/api/binance/include/
)

target_link_libraries(GeneralDataParserTest PRIVATE
    Qt6::Core
    Qt6::Network

    GTest::gtest_main

    BinanceAPI
)

include(GoogleTest)
gtest_discover_tests(GeneralDataParserTest)
