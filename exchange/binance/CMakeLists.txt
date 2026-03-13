add_library(BinanceAPI
    data/APIEndpoints.h
    data/Enums.h
    data/Errors.h
    data/Filters.h
    data/GeneralData.h
    data/MarketData.h
    data/TradingData.h

    http/BinanceHttpClient.h
    converters/EnumConverter.h
    converters/ErrorConverter.h
    converters/FilterConverter.h
    parsers/GeneralDataParser.h
    parsers/MarketDataParser.h
    repositories/BinanceGeneralDataRepository.h

    http/BinanceHttpClient.cpp
    converters/EnumConverter.cpp
    converters/ErrorConverter.cpp
    converters/FilterConverter.cpp
    parsers/GeneralDataParser.cpp
    parsers/MarketDataParser.cpp
    repositories/BinanceGeneralDataRepository.cpp
)

target_include_directories(BinanceAPI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE
    Qt6::Core
    Qt6::Network
)
