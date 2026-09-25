include(FetchContent)
FetchContent_Declare(
    simpleble                             
    GIT_REPOSITORY https://github.com/simpleble/simpleble.git
    GIT_TAG        v1.1.0                 
    SOURCE_SUBDIR  simpleble              
)

FetchContent_Declare(                                                      # ← NEW
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(simpleble json)

add_library(blc STATIC
    src/protocol.cpp
    src/stationmanager.cpp
    src/v1id.cpp
)
target_include_directories(blc PUBLIC include)
target_link_libraries(blc PRIVATE 
    simpleble::simpleble
    nlohmann_json::nlohmann_json
)