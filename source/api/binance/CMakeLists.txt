add_library(BinanceAPI
    include/APIEndpoints.h
    include/BinanceAPI.h
    include/EnumConverter.h
    include/Enums.h
    include/ErrorConverter.h
    include/Errors.h
    include/FilterConverter.h
    include/Filters.h
    include/GeneralData.h

    src/BinanceAPI.cpp
    src/EnumConverter.cpp
    src/ErrorConverter.cpp
    src/FilterConverter.cpp
)

target_include_directories(BinanceAPI PUBLIC include/)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(BinanceAPI PRIVATE Qt6::Core Qt6::Network)
