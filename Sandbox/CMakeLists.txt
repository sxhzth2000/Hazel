cmake_minimum_required(VERSION 3.20)
project(Sandbox)


set(CMAKE_CXX_STANDARD 17)

# 查找所有 Sandbox 代码文件

file(GLOB_RECURSE HAZEL_SOURCES
   #     ../Hazel/src/Hazel/Core/Application.cpp
    #    ../Hazel/src/Hazel/Core/Log.cpp
)

file(GLOB_RECURSE SANDBOX_SOURCES
        "src/*.cpp"
)



# 仅添加 Sandbox 的源文件
add_executable(Sandbox
        src/Sandbox.cpp
        src/Sandbox2D.cpp
          # 显式列出文件更安全
)

    target_link_libraries(Sandbox PRIVATE Hazel)
# 包含 Hazel 的头文件目录
target_include_directories(Sandbox PUBLIC
        ${CMAKE_SOURCE_DIR}/Hazel/src
        ${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include
        ${CMAKE_SOURCE_DIR}/Sandbox/src
)

# Windows 专用设置
if (WIN32)
    target_compile_definitions(Sandbox PUBLIC HZ_PLATFORM_WINDOWS)
endif()


# MSVC 编译器设置
if (MSVC)
    set(CMAKE_CXX_FLAGS "/utf-8")
    set(CMAKE_C_FLAGS "/utf-8")
endif()


# 运行时 DLL 需要在 bin 目录
set_target_properties(Sandbox PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

