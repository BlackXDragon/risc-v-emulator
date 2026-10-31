cmake_minimum_required(VERSION 3.20)

project(risc-v-emulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	src/cpu.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)