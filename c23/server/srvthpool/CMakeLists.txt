add_executable(srvthpool main.c)
target_link_libraries(srvthpool
        PRIVATE
        requesthdl
)
target_include_directories(srvthpool PRIVATE ../requesthdl)
install(TARGETS srvthpool)