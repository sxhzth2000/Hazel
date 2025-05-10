

cmake_minimum_required(VERSION 3.20)

# 设置项目名和语言
project(Hazel LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)





# 查找所有 Hazel 代码文件
file(GLOB_RECURSE HAZEL_SOURCES
        src/*.cpp
)
file(GLOB_RECURSE HAZEL_HANDER "src/*.h")
file(GLOB IMGUI_SOURCES
        "vendor/imgui/*.cpp"
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        vendor/imgui/backends/imgui_impl_glfw.cpp
)


# 构建 Hazel 作为动态库
add_library(Hazel SHARED
        ${HAZEL_SOURCES}
        ${IMGUI_SOURCES}
        Platform/Windows/WindowsWindow.cpp
        vendor/glad/src/glad.c
        Platform/Windows/WindowsInput.cpp
        src/Hazel/Renderer/GraphicsContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLContext.h
        src/Hazel/Renderer/Shader.cpp
        src/Hazel/Renderer/Shader.h
        src/Hazel/Renderer/Buffer.cpp
        src/Hazel/Renderer/Buffer.h
        Platform/OpenGL/OpenglBuffer.cpp
        Platform/OpenGL/OpenglBuffer.h
        src/Hazel/Renderer/Renderer.cpp
        src/Hazel/Renderer/Renderer.h
        src/Hazel/Renderer/VertexArray.cpp
        src/Hazel/Renderer/VertexArray.h
        Platform/OpenGL/OpenGLVertexArray.cpp
        Platform/OpenGL/OpenGLVertexArray.cpp
        Platform/OpenGL/OpenGLVertexArray.h
        src/Hazel/Renderer/RendererAPI.h
        src/Hazel/Renderer/RendererAPI.cpp
        src/Hazel/Renderer/RenderCommand.h
        src/Hazel/Renderer/RenderCommand.cpp
        Platform/OpenGL/OpenGLRendererAPI.cpp
        Platform/OpenGL/OpenGLRendererAPI.h
        src/Hazel/Renderer/OrthographicCamera.cpp
        src/Hazel/Renderer/OrthographicCamera.h
        src/Hazel/Core/TimeStep.h
        src/Hazel/Renderer/OpenglShader.cpp
        src/Hazel/Renderer/OpenglShader.h
        src/Hazel/Renderer/Texture.cpp
        src/Hazel/Renderer/Texture.h
        Platform/OpenGL/OpenGLTexture.cpp
        Platform/OpenGL/OpenGLTexture.h
        vendor/STB_image/stb_image.h
        vendor/STB_image/stb_image.cpp
)

message(STATUS "Hazel sources: ${HAZEL_SOURCES}")


# 添加 GLFW 源码目录
add_subdirectory(vendor/GLFW)

# 链接 GLFW（它提供了 glfw 这个 target）
target_link_libraries(Hazel PRIVATE glfw opengl32)




# 头文件路径，确保 Sandbox 可以正确引用 Hazel 头文件
target_include_directories(Hazel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform
    ${CMAKE_SOURCE_DIR}/Hazel/vendor/GLM
    ${CMAKE_SOURCE_DIR}/Hazel/vendor
)

set(CMAKE_PCH_EXTENSION .cpp)  # 👈 强制使用 .cpp 编译 cmake_pch

# 设置 PCH 仅用于 C++ 编译单元
target_precompile_headers(Hazel PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/hzpch.h>
)

set_source_files_properties(vendor/glad/src/glad.c PROPERTIES LANGUAGE C)


# Windows 专用设置
if (WIN32)
    target_compile_definitions(Hazel PUBLIC HZ_PLATFORM_WINDOWS HZ_BUILD_DLL IMGUI_DLL_EXPORTS)
endif()

# MSVC 编译器设置
#if (MSVC)
#    set(CMAKE_CXX_FLAGS "/utf-8")
#    set(CMAKE_C_FLAGS "/utf-8")
#endif()
if (MSVC)
    # 用于 C++
    target_compile_options(Hazel PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/utf-8>)
    # 用于 C
    target_compile_options(Hazel PRIVATE $<$<COMPILE_LANGUAGE:C>:/utf-8>)
endif()



# 设置输出目录
set_target_properties(Hazel PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int  # 导入库 (.lib)
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int  # 共享库 (.dll)
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin  # 运行库 (.dll)
)

