add_library(Models
    include/SymbolsModel.h
    
    src/SymbolsModel.cpp
)

target_include_directories(Models PUBLIC include/)

# Find Qt6 modules
find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(Models PRIVATE
    APICommon
    Qt6::Core
    Qt6::Network
)
