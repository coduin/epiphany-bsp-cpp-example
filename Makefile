EBSP=ext/ebsp
ESDK=${EPIPHANY_HOME}
ELDF=${EBSP}/ebsp_fast.ldf

CPPFLAGS=-std=c++14 -Wall -O3 -ffast-math
E_CPPFLAGS=-std=c++14 -Wall -Os -fno-tree-loop-distribute-patterns -fno-exceptions

INCLUDES = \
	-I${EBSP}/include\
	-I${ESDK}/tools/host/include

LIBS = \
	-L${EBSP}/lib

HOST_LIBS = \
	-L /usr/arm-linux-gnueabihf/lib \
	-L${ESDK}/tools/host/lib

E_LIBS = \
	-L${ESDK}/tools/host/lib

HOST_LIB_NAMES = -lhost-bsp -le-hal -le-loader
E_LIB_NAMES = -le-bsp -le-lib

all: ebsp cpp

ebsp:
	@cd ext/ebsp && make

bin/%: src/%.cpp
	@echo "CXX $<"
	@g++ $(CPPFLAGS) $(INCLUDES) -o $@ $< $(LIBS) $(HOST_LIBS) $(HOST_LIB_NAMES)

bin/%.elf: src/%.cpp
	@echo "CXX $<"
	@e-g++ $(E_CPPFLAGS) -T ${ELDF} $(INCLUDES) -o $@ $< src/reduce_binary_size.cpp $(LIBS) $(E_LIBS) $(E_LIB_NAMES)

cpp: bin/ bin/host_cpp bin/e_cpp.elf

bin/:
	@mkdir -p bin
