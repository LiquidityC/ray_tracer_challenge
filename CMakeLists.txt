cmake_minimum_required(VERSION 3.10)

project(ray-tracer-challenge VERSION 0.1.0)

add_subdirectory(unity)

add_executable(tracer
	src/main.c
	src/tuple.c
	src/float.c
	)
target_include_directories(tracer PRIVATE include)
target_link_libraries(tracer PRIVATE m)

enable_testing()

function(generate_test)
	cmake_parse_arguments(GENERATE_TEST "" "LABEL" "SOURCES" ${ARGN})
	add_executable(${GENERATE_TEST_LABEL} ${GENERATE_TEST_SOURCES})
	target_include_directories(${GENERATE_TEST_LABEL} PRIVATE include)
	target_link_libraries(${GENERATE_TEST_LABEL} PRIVATE unity m)
	add_test(NAME ${GENERATE_TEST_LABEL} COMMAND ${GENERATE_TEST_LABEL})
endfunction()

generate_test(
	LABEL test_tuple
	SOURCES test/test_tuple.c src/tuple.c src/float.c
	)
