add_executable(srvseqcpp main.cpp)
target_link_libraries(srvseqcpp PRIVATE requesthdlcpp)
target_include_directories(srvseqcpp PRIVATE ../requesthdl)
install(TARGETS srvseqcpp)