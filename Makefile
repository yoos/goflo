goflo: src/goflo.cpp
	clang++ -std=c++11 -O2 src/goflo.cpp -o goflo -Wall `pkg-config opencv --libs --cflags`

clean:
	rm goflo