cmake_minimum_required(VERSION 3.5)

project(product_database_caching LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS ${PROJECT_SOURCE_DIR}/product.h
            ${PROJECT_SOURCE_DIR}/fake_database.h
            ${PROJECT_SOURCE_DIR}/cache_implementation.h
            ${PROJECT_SOURCE_DIR}/product_cache.h)


add_executable(product_database_caching main.cpp ${HEADERS})

install(TARGETS product_database_caching
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
