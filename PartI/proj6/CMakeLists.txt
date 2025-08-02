cmake_minimum_required(VERSION 3.5.0)
project(project6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#设置源代码路径
set(CPP ${PROJECT_SOURCE_DIR}/cpp)
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)
#设置可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#编译源文件
add_subdirectory(${CPP})
