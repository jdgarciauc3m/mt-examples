add_executable(srvproc main.c)
target_link_libraries(srvproc
        PRIVATE
        requesthdl
)
target_include_directories(srvproc PRIVATE ../requesthdl)
install(TARGETS srvproc)