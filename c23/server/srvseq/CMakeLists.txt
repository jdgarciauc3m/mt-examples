add_executable(srvseq main.c)
target_link_libraries(srvseq
        PRIVATE
        requesthdl
)
target_include_directories(srvseq PRIVATE ../requesthdl)
install(TARGETS srvseq)
