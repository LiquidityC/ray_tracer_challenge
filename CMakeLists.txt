cmake_minimum_required(VERSION 3.10)

project(ray-tracer-challenge VERSION 0.1.0)

add_subdirectory(unity)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS src/*.c)
add_executable(tracer ${SOURCE_FILES})
target_compile_options(tracer PRIVATE -fsanitize=address -g)
target_include_directories(tracer PRIVATE include)
target_link_options(tracer PRIVATE -fsanitize=address)
target_link_libraries(tracer PRIVATE m asan)

enable_testing()

# Remove main.c from SOURCE_FILES list
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

# Find the test sources
file(GLOB TEST_SOURCE_FILES CONFIGURE_DEPENDS test/*.c)
file(GLOB TEST_COMMON_SOURCE_FILES CONFIGURE_DEPENDS test/common/*.c)

function(generate_test)
	cmake_parse_arguments(GENERATE_TEST "" "LABEL" "SOURCES" ${ARGN})
	add_executable(${GENERATE_TEST_LABEL} ${GENERATE_TEST_SOURCES} ${TEST_COMMON_SOURCE_FILES})
	#target_compile_options(${GENERATE_TEST_LABEL} PRIVATE -fsanitize=address -g)
	target_include_directories(${GENERATE_TEST_LABEL} PRIVATE include test/common)
	#target_link_options(${GENERATE_TEST_LABEL} PRIVATE -fsanitize=address)
	target_link_libraries(${GENERATE_TEST_LABEL} PRIVATE unity m)
	add_test(NAME ${GENERATE_TEST_LABEL} COMMAND ${GENERATE_TEST_LABEL})
endfunction()


foreach(F IN LISTS TEST_SOURCE_FILES)
	get_filename_component(TEST_NAME ${F} NAME_WE)
	generate_test(
		LABEL ${TEST_NAME}
		SOURCES ${F} ${SOURCE_FILES}
		)
endforeach()
