cmake_minimum_required(VERSION 3.20)
project(Hazel)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)






# 查找所有 Hazel 代码文件
file(GLOB_RECURSE HAZEL_SOURCES
        src/*.cpp
)
file(GLOB_RECURSE HAZEL_HANDER "src/*.h")



# 构建 Hazel 作为动态库
add_library(Hazel SHARED
        ${HAZEL_SOURCES}
        Platform/Windows/WindowsWindow.cpp
        Platform/Windows/WindowsWindow.h
        src/Window.h
        src/Hazel/Layer.cpp
        src/Hazel/Layer.h
        src/Hazel/LayerStack.cpp
        src/Hazel/LayerStack.h

)



# 添加 GLFW 源码目录
add_subdirectory(vendor/GLFW)

# 链接 GLFW（它提供了 glfw 这个 target）
target_link_libraries(Hazel PRIVATE glfw opengl32)




# 头文件路径，确保 Sandbox 可以正确引用 Hazel 头文件
target_include_directories(Hazel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
)

target_precompile_headers(Hazel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hzpch.h)

# Windows 专用设置
if (WIN32)
    target_compile_definitions(Hazel PUBLIC HZ_PLATFORM_WINDOWS HZ_BUILD_DLL)
endif()

# MSVC 编译器设置
if (MSVC)
    set(CMAKE_CXX_FLAGS "/utf-8")
    set(CMAKE_C_FLAGS "/utf-8")
endif()



# 设置输出目录
set_target_properties(Hazel PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int  # 导入库 (.lib)
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int  # 共享库 (.dll)
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin  # 运行库 (.dll)
)

