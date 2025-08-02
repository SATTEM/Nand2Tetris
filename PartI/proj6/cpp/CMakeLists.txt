cmake_minimum_required(VERSION 3.5.0)
project(HackAssembler)
#获取本层源文件
file(GLOB PROJECT_SOURCE CONFIGURE_DEPENDS ${CPP}/*.cpp)
#添加可执行文件
add_executable(${PROJECT_NAME})
#添加源文件
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE})
#添加头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADPATH})