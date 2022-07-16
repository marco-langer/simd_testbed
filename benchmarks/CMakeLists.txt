include(FetchContent)

set(BENCHMARK_ENABLE_TESTING off)    # to suppress benchmark internal tests

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

add_subdirectory(algorithm)
add_subdirectory(linear_algebra)
add_subdirectory(numeric)
add_subdirectory(statistics)
