# CMake Tutorial
---
[教程视频](https://www.bilibili.com/video/BV1rR4y1E7n9/?spm_id_from=333.337.search-card.all.click&vd_source=533dd018ea2305035a3873b41ddfc3ed)

## CMake
- CMake本身不带编译工具，所以开发者需要一个完整的C++的编译环境

## CMakeLists.txt文件基础语法
- cmake_minimum_required(VERSION 3.10)  CMake所需的最低版本
- project(Example) 工程名字和输出的项目的文件名
- add_executable(Example main.cpp) 表示我们的项目需要构建一个可执行文件并且是由源代码mian.cpp构建而来
- find_package(imgui REQUIRED) 寻找所需要的cpp库，需要确保这些库已经在计算机中安装，并且支持CMake，后面的第一个参数是这个库的名称，第二个参数是表示这个库是必须的，如果没有这个库的话会报错
- file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.h") 通过通配符匹配所有的项目源文件（这里只写了头文件一类）
- target_compile_features(cxx_std_20) 打开对cpp20的支持
- target_link_libraries()链接库

## CMake的通配符
- ${CMAKE_PROJECT_NAME}
- ${SRC_FILES} 自定义的（见上文）
- 

## CMake和第三方库的安装
- 第三方库的安装工具：vcpkg
- 

## CMake指令
- 配置项目：cmake -S . -B build
- 构建项目：cmake --build build

## Tips:
- 如果CMakeLists 文件没有改变的话，重新编译项目只需要使用make就行了
