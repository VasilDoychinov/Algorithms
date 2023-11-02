cmake_minimum_required(VERSION 3.5)

project(sortHeap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(MY_LOGGER_DIR "~/src/Logger")

add_executable(sortHeap test_sort.cpp
                        ${MY_LOGGER_DIR}/lib/Logger_impl.cpp                      # library: Logger
                        src/heap_sort.hpp src/heap_sort.cpp
              )

target_include_directories(sortHeap PUBLIC ${MY_LOGGER_DIR}/include)

include(GNUInstallDirs)
install(TARGETS sortHeap
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
