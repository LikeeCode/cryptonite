add_library(BinanceAPI
    include/APIEndpoints.h
    include/BinanceAPI.h
    include/enums/Converter.h
    include/enums/Enums.h
    include/errors/Converter.h
    include/errors/Errors.h
    include/filters/Converter.h
    include/filters/Filters.h
    include/GeneralData.h
    include/GeneralDataParser.h

    src/BinanceAPI.cpp
    src/enums/Converter.cpp
    src/errors/Converter.cpp
    src/filters/Converter.cpp
    src/GeneralDataParser.cpp
)

target_include_directories(BinanceAPI PUBLIC include/)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE Qt6::Core Qt6::Network)
