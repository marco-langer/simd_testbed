set(BENCHMARK_NAME benchmarks_image_processing)

set(BENCHMARK_SOURCES
    ../main.cpp
    threshold.cpp
)

add_executable(${BENCHMARK_NAME} ${BENCHMARK_SOURCES})

set_property(TARGET ${BENCHMARK_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${BENCHMARK_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${BENCHMARK_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(${BENCHMARK_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2 -O3 -mavx2 -mfma>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /O2>)

target_include_directories(${BENCHMARK_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_libraries(${BENCHMARK_NAME} benchmark::benchmark fmt::fmt ${OpenCV_LIBS})
