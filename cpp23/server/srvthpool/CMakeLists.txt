add_executable(srvthpoolcpp main.cpp)
target_link_libraries(srvthpoolcpp
        PRIVATE
        requesthdlcpp
)
target_include_directories(srvthpoolcpp PRIVATE ../requesthdl)
install(TARGETS srvthpoolcpp)