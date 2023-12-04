cmake_minimum_required(VERSION 3.6)

project(printlib  LANGUAGES CXX)

add_library(${PROJECT_NAME}
    include/iprinter.hpp
    include/consoleprinter.hpp
    # include/fileprinter.hpp
    src/consoleprinter.cpp
    # src/fileprinter.cpp
)

# if (${BUILD_TESTING})
#     add_subdirectory(tests)
# endif()

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
