spacer-a:
    g++ -static -I /home/hari/code/z3-deep-space/src/api/c++ -I /home/hari/code/z3-deep-space/src/api -L /home/hari/code/z3-deep-space/build -o spacer-a parallel-arrays.cpp -lz3 -Wl,--whole-archive -lrt -lpthread -Wl,--no-whole-archive -static-libgcc -static-libstdc++

spacer-l:
    g++ -static -I /home/hari/code/z3-deep-space/src/api/c++ -I /home/hari/code/z3-deep-space/src/api -L /home/hari/code/z3-deep-space/build -o spacer-l parallel-lra.cpp -lz3 -Wl,--whole-archive -lrt -lpthread -Wl,--no-whole-archive -static-libgcc -static-libstdc++
