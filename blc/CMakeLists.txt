include(FetchContent)
FetchContent_Declare(
    simpleble                             
    GIT_REPOSITORY https://github.com/simpleble/simpleble.git
    GIT_TAG        v1.1.0                 
    SOURCE_SUBDIR  simpleble              
)
FetchContent_MakeAvailable(simpleble)

add_library(blc STATIC
    src/protocol.cpp
    src/stationmanager.cpp
)
target_include_directories(blc PUBLIC include)
target_link_libraries(blc PRIVATE simpleble::simpleble)