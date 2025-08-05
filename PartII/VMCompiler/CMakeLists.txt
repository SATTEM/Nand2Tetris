cmake_minimum_required(VERSION 3.5.0)
project(VMC)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#设置代码路径
set(CPP ${PROJECT_SOURCE_DIR}/cpp)
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)
#设置中间文件存放路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBPATH})
#设置可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#编译源文件
add_subdirectory(${CPP}/File)
add_subdirectory(${CPP}/Command)
add_subdirectory(${CPP})
