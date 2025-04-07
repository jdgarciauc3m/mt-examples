add_executable(racevar main.c)
add_executable(racevartsan main.c)
target_compile_options(racevartsan PRIVATE -fsanitize=thread)
target_link_options(racevartsan PRIVATE -fsanitize=thread)