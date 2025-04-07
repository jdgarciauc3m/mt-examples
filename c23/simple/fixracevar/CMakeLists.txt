add_executable(fixracevar main.c)
add_executable(fixracevartsan main.c)
target_compile_options(fixracevartsan PRIVATE -fsanitize=thread)
target_link_options(fixracevartsan PRIVATE -fsanitize=thread)