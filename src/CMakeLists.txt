set(target "coil-solver")

add_executable(${target}
    http_handler.hpp
    http_handler.cpp

    main.cpp
)

target_include_directories("${target}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries("${target}"
    PRIVATE
        libcurl.so
)