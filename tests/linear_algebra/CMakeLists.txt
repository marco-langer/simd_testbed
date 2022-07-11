set(TEST_NAME tests_linear_algebra)

set(TEST_SOURCES
    matrix.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(${TEST_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2 -mavx2 -mfma>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /O2>)

target_include_directories(${TEST_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_libraries(${TEST_NAME} Catch2::Catch2WithMain fmt::fmt)

catch_discover_tests(${TEST_NAME})
