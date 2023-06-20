cmake_minimum_required(VERSION 3.10)
project(windmoon)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    option(BUILD_HTML "Build html also!" ON)

    set(EMSCRIPTEN TURE)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
endif()

# 设置CPP版本
if (EMSCRIPTEN)
	set(CMAKE_C_COMPILER "emcc")
	set(CMAKE_CXX_COMPILER "em++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --bind -s ALLOW_MEMORY_GROWTH=1 -lwebsocket.js -sPROXY_POSIX_SOCKETS -pthread -sPROXY_TO_PTHREAD")
else()
	set(CMAKE_CXX_STANDARD 11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
	set(WASM_ENGINE_FLAGS "${WASM_ENGINE_FLAGS} -lwebsocket.js -sPROXY_POSIX_SOCKETS -pthread -sPROXY_TO_PTHREAD")
endif()

set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
if (EMSCRIPTEN)
	set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.bc)
	set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.bc)
	set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
endif()
find_package(OpenSSL REQUIRED)


message(STATUS "OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")
message(STATUS "OPENSSL_SSL_LIBRARY: ${OPENSSL_SSL_LIBRARY}")
message(STATUS "OPENSSL_CRYPTO_LIBRARY: ${OPENSSL_CRYPTO_LIBRARY}")

# 设置项目中的头文件目录
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/resources
	${PROJECT_SOURCE_DIR}/lib
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
if(APPLE)
	target_link_libraries(${PROJECT_NAME}
		${OPENSSL_LIBRARIES}
		${CoreFoundation_LIBRARY}
	)
elseif(EMSCRIPTEN)
	target_link_libraries(${PROJECT_NAME} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
else()
	target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
endif()

# if (EMSCRIPTEN)
# 	set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY
# 		LINK_FLAGS_DEBUG " -s SOCKET_DEBUG=1")
# endif()

# 拷贝资源文件
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})