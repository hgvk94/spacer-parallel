spacer-a:
	g++ -o spacer-a parallel-arrays.cpp -I/home/hari/code/z3-deep-space/src/api/c++ -I/home/hari/code/z3-deep-space/src/api /home/hari/code/z3-deep-space-release/libz3.a -lpthread -O3
spacer-l:
	g++ -o spacer-l parallel-lra.cpp -I/home/hari/code/z3-deep-space/src/api/c++ -I/home/hari/code/z3-deep-space/src/api /home/hari/code/z3-deep-space-release/libz3.a -lpthread -O3
