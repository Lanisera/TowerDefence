cmake_minimum_required(VERSION 3.15)

project(TowerDefence CXX)

# 生成json文件方便coc实现代码补全
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# sdl2_gfx库未提供cmake文件，需手动获取其动态链接库和头文件
set(SDL2_gfx_LIBRARIES "/usr/lib/libSDL2_gfx.so")
set(SDL2_gfx_INCLUDE_DIRS "/usr/include/SDL2/")

# 寻找sdl链接库
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(cJSON REQUIRED)

set(SOURCE_DIR src)
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(td ${SOURCES})

target_include_directories(td PUBLIC
	${SDL2_INCLUDE_DIRS}
	${SDL2_image_INCLUDE_DIRS}
	${SDL2_ttf_INCLUDE_DIRS}
	${SDL2_mixer_INCLUDE_DIRS}
	${SDL2_gfx_INCLUDE_DIRS}
	${cJSON_INCLUDE_DIRS}
)

target_link_libraries(td
	SDL2::SDL2
	SDL2_ttf::SDL2_ttf
	SDL2_image::SDL2_image
	SDL2_mixer::SDL2_mixer
	${SDL2_gfx_LIBRARIES}
	${CJSON_LIBRARIES}
)

