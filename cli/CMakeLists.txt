add_executable(bsbctl main.cpp)           # build a program called "bsbctl"
target_link_libraries(bsbctl PRIVATE blc) # it uses the blc library (and gets its include path automatically)