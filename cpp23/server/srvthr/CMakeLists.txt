add_executable(srvthrcpp main.cpp)
target_link_libraries(srvthrcpp
        PRIVATE
        requesthdlcpp
)
target_include_directories(srvthrcpp PRIVATE ../requesthdl)
install(TARGETS srvthrcpp)