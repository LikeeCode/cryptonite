add_library(BinanceAPI
    include/APIEndpoints.h
    include/BinanceAPI.h
    include/enums/EnumConverter.h
    include/enums/Enums.h
    include/errors/ErrorConverter.h
    include/errors/Errors.h
    include/filters/TypeConverter.h
    include/filters/Filters.h
    include/GeneralData.h
    include/GeneralDataParser.h

    src/BinanceAPI.cpp
    src/enums/EnumConverter.cpp
    src/errors/ErrorConverter.cpp
    src/filters/TypeConverter.cpp
    src/GeneralDataParser.cpp
)

target_include_directories(BinanceAPI PUBLIC include/)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE Qt6::Core Qt6::Network)
