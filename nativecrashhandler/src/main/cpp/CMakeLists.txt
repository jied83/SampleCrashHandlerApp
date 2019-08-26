project(chandler C CXX ASM)
cmake_minimum_required(VERSION 3.6)
set(ANDROID ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_USE_RELATIVE_PATHS ON)
include_directories(
        "${CMAKE_SOURCE_DIR}/client"
        "${CMAKE_SOURCE_DIR}/client/linux"
        "${CMAKE_SOURCE_DIR}/client/linux/handler"
        "${CMAKE_SOURCE_DIR}/client/linux/minidump_writer"
        "${CMAKE_SOURCE_DIR}/client/linux/microdump_writer"
        "${CMAKE_SOURCE_DIR}/common"
        "${CMAKE_SOURCE_DIR}/common/linux"
        "${CMAKE_SOURCE_DIR}/jni")
set(CRASHHANDLER_SRCS
        client/linux/crash_generation/crash_generation_client.cc
        client/linux/dump_writer_common/thread_info.cc
        client/linux/dump_writer_common/ucontext_reader.cc
        client/linux/handler/exception_handler.cc
        client/linux/handler/minidump_descriptor.cc
        client/linux/log/log.cc
        client/linux/microdump_writer/microdump_writer.cc
        client/linux/minidump_writer/linux_dumper.cc
        client/linux/minidump_writer/linux_ptrace_dumper.cc
        client/linux/minidump_writer/minidump_writer.cc
        client/minidump_file_writer.cc
        common/android/breakpad_getcontext.S
        common/convert_UTF.c
        common/md5.cc
        common/string_conversion.cc
        common/linux/elfutils.cc
        common/linux/file_id.cc
        common/linux/guid_creator.cc
        common/linux/linux_libc_support.cc
        common/linux/memory_mapped_file.cc
        common/linux/safe_readlink.cc
        jni/crashhandlerJni.cc)

set(CRASHHANDLER_LIBRARY ${PROJECT_NAME})
add_library(${CRASHHANDLER_LIBRARY} SHARED ${CRASHHANDLER_SRCS})
target_include_directories(chandler PUBLIC
        ${CMAKE_SOURCE_DIR}
        "/common/android/include"
        )
