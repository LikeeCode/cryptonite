add_library(Models
    SymbolsModel.h

    SymbolsModel.cpp
)

target_include_directories(Models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(Models PRIVATE
    BinanceAPI
    Qt6::Core
    Qt6::Network
)