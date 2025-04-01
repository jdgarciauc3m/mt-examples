add_executable(srvproccpp main.cpp)
target_link_libraries(srvproccpp
        PRIVATE
        requesthdlcpp
)
target_include_directories(srvproccpp PRIVATE ../requesthdl)
install(TARGETS srvproccpp)