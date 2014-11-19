goflo: src/*.cpp
	clang++ -std=c++11 -O2 src/*.cpp -Isrc -o goflo -Wall `pkg-config opencv --libs --cflags`

clean:
	rm goflo
