cmake_minimum_required(VERSION 3.5.0)
project(Commands)
#获取本层源文件
file(GLOB CURRENT_FILE CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp)
#添加可执行文件
add_library(${PROJECT_NAME} STATIC ${CURRENT_FILE})
#添加源文件
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE})
#添加头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADPATH})
