cmake_minimum_required(VERSION 3.10)

project(TypeAhead)

set(HEADER_FILES
		WordTree.hpp
		rlutil.h)

set(SOURCE_FILES
		WordTree.cpp)

set(UNIT_TEST_FILES
		TestWordTree.cpp)

add_executable(TypeAhead
		${HEADER_FILES}
		${SOURCE_FILES}
		main.cpp)

add_executable(UnitTestRunner
		${HEADER_FILES}
		${SOURCE_FILES}
		${UNIT_TEST_FILES})

set_property(TARGET TypeAhead PROPERTY CXX_STANDARD 17)
set_property(TARGET UnitTestRunner PROPERTY CXX_STANDARD 17)

#
#Compiler target_compile_options
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		target_compile_options(TypeAhead PRIVATE /W4 /permissive-)
		target_compile_options(UnitTestRunner PRIVATE /W4 /permissive-)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		target_compile_options(TypeAhead PRIVATE -Wall -Wextra -pedantic -O3)
		target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic -O3)

endif()

#
# ClangFormat
#
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
		unset(SOURCE_FILES_PATHS)
		foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES} main.cpp)
				get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
		    set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
		endforeach()

		add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS}
		)

		add_dependencies(TypeAhead ClangFormat)
else()
    message("Unable to find clang-format")
endif()

#
#Google Test
#
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

target_link_libraries(UnitTestRunner gtest_main)
