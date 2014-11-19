CXX=clang++
RM=rm -f

CXXFLAGS=-Wall -Wextra -std=c++11 -Isrc/ -O2 -g
LDFLAGS=$(shell pkg-config opencv --libs --cflags) -L/opt/cuda/lib64

SRCS=$(shell find src/ -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

all: goflo

goflo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o goflo $(OBJS) $(LDFLAGS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
