add_library(blc STATIC                    # build a library called "blc"
    src/protocol.cpp                      # only protocol for now; stationmanager comes with SimpleBLE
)
target_include_directories(blc PUBLIC include)   # headers are in include/; PUBLIC = users of blc get this path too