add_library(BinanceAPI
    data/APIEndpoints.h
    data/GeneralData.h
    data/MarketData.h
    data/TradingData.h
    enums/Enums.h
    errors/Errors.h
    filters/Filters.h
    http/BinanceAPI.h
    parsers/EnumConverter.h
    parsers/ErrorConverter.h
    parsers/FilterConverter.h
    parsers/GeneralDataParser.h
    parsers/MarketDataParser.h
    
    http/BinanceAPI.cpp
    parsers/EnumConverter.cpp
    parsers/ErrorConverter.cpp
    parsers/FilterConverter.cpp
    parsers/GeneralDataParser.cpp
    parsers/MarketDataParser.cpp
)

target_include_directories(BinanceAPI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE
    Qt6::Core
    Qt6::Network
)
