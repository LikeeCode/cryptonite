add_library(BinanceAPI
    include/enums/Converter.h
    include/enums/Enums.h
    include/errors/Converter.h
    include/errors/Errors.h
    include/filters/Converter.h
    include/filters/Filters.h
    include/rest-api/APIEndpoints.h
    include/rest-api/BinanceAPI.h
    include/rest-api/GeneralData.h
    include/rest-api/GeneralDataParser.h
    include/rest-api/MarketData.h
    
    src/enums/Converter.cpp
    src/errors/Converter.cpp
    src/filters/Converter.cpp
    src/rest-api/BinanceAPI.cpp
    src/rest-api/GeneralDataParser.cpp
)

target_include_directories(BinanceAPI PUBLIC include/)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE
    APICommon
    Qt6::Core
    Qt6::Network
)
