cmake_minimum_required(VERSION 3.25)

project(jpar 
    VERSION 0.0.1 
    LANGUAGES CXX
)


if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall          
        -Wextra         
        -Wpedantic     
    )

        link_libraries(-fsanitize=address -fsanitize=undefined)

endif()


set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/includes  
)

include(GNUInstallDirs)

add_subdirectory(src)
