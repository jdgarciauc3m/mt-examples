add_executable(srvthr main.c)
target_link_libraries(srvthr
        PRIVATE
        requesthdl
)
target_include_directories(srvthr PRIVATE ../requesthdl)
install(TARGETS srvthr)