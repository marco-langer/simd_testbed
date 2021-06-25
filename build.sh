g++ -std=c++20 -c -O2 simd.cpp -march=skylake-avx512 && objdump -d simd.o > dump
