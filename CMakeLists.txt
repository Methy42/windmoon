cmake_minimum_required(VERSION 3.10)
project(windmoon)

# 设置CPP版本
set(CMAKE_CXX_STANDARD 11)

set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
find_package(OpenSSL REQUIRED)

message(STATUS "OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

# 设置项目中的头文件目录
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/resources
	$ENV{OPENSSL_ROOT_DIR}/include
	$ENV{CMAKE_INCLUDE_PATH}
)
link_libraries(${OPENSSL_LIBRARIES})

# 在 macOS 平台上链接 CoreFoundation.framework 库
if (APPLE)
    find_library(CoreFoundation_LIBRARY CoreFoundation)
endif()

# 设置源文件目录
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 添加源文件和头文件路径
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/**/*.cpp")
include_directories(${LIBUV_INCLUDE_DIRS})

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_FILES})

# 链接库
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
if(APPLE)
	target_link_libraries(${PROJECT_NAME} ${CoreFoundation_LIBRARY})
endif()


# 拷贝资源文件
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})