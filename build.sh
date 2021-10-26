g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -c -O2 simd.cpp -march=skylake-avx512 && objdump -d simd.o > dump.txt
