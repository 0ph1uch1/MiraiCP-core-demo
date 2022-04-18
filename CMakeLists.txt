cmake_minimum_required(VERSION 3.22)
# set using utf8 for msvc
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
project(miraicp_core_demo)

set(CMAKE_CXX_STANDARD 17)
# -- 获取JNI, 这一部分不需要改 --
set(JAVA_AWT_LIBRARY NotNeeded)
# need java_jvm_library under linux
#set(JAVA_JVM_LIBRARY NotNeeded)
set(JAVA_AWT_INCLUDE_PATH NotNeeded)
find_package(JNI REQUIRED)
if (JNI_FOUND)
    message(STATUS "FOUND JNI IN ${JAVA_INCLUDE_PATH}")
    set(SOURCE_PATH
            ${CMAKE_CURRENT_SOURCE_DIR}/MiraiCP/3rd_includes/
            ${CMAKE_CURRENT_SOURCE_DIR}/MiraiCP/3rd_includes/utf8
            ${CMAKE_CURRENT_SOURCE_DIR}/MiraiCP/3rd_includes/utf8/utf8
            ${CMAKE_CURRENT_SOURCE_DIR}/MiraiCP
            ${JAVA_INCLUDE_PATH}/
            ${JAVA_INCLUDE_PATH2}/
            )
else ()
    message(STATUS "Cannot find JNI")
endif ()
if (WIN32)
    ADD_DEFINITIONS(-D_JVM_DLL_PATH=\"${JAVA_INCLUDE_PATH}/../bin/server/jvm.dll\")
else (WIN32)
    ADD_DEFINITIONS(-D_JVM_DLL_PATH=\"\")
endif (WIN32)
# -- end --

# 设立一个executable 目标, 需要添加MiraiCP.cpp和core.cpp
add_executable(MiraiCP_core_demo
        main.cpp
        MiraiCP/MiraiCP.cpp
        MiraiCP/core.cpp)
# 指定 MiraiCP 已经依赖库的头文件寻找路径
target_include_directories(MiraiCP_core_demo PUBLIC ${SOURCE_PATH})
# 如果在unix情况下, 链接JVM的库, 如果确定在win下使用可以删除
if (UNIX)
    target_link_libraries(MiraiCP_core_demo ${JAVA_JVM_LIBRARY})
endif (UNIX)
