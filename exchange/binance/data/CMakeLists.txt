add_library(Data
    APIEndPoints.h
    GeneralData.h
    MarketData.h
    TradingData.h
)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(Data PRIVATE
    Qt6::Core
    Qt6::Network
)