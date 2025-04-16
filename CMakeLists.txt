

cmake_minimum_required(VERSION 3.28)
project(Hazelprj)

# 确保生成的 .sln 和 VS 项目文件都在 CMake 根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)





add_subdirectory(Hazel)
add_subdirectory(Sandbox)






