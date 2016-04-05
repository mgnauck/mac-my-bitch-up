# makefile for macmybitchup

CPP = g++

OBJ = Concentrical.o Greets.o Squared.o Tunnel.o Tube.o Blocks.o Title.o Last.o Break.o Animation.o BASSWrapper.o Blending.o Blitter.o Constants.o DisplacementMapper.o EffectHandler.o GFXHelper.o ImageHandler.o main.o Noise.o SDLWrapper.o Fade.o 

TARGET = macbitch
LDFLAGS = -lm -L./
CFLAGS = -O3 $(INCLUDES)

CFLAGS += -DOS_X -DSDL -I/sw/include/ `sdl-config --cflags`
LDFLAGS += `sdl-config --static-libs` -lbass -framework Cocoa

%.o: %.cxx $(HEADERS)
	$(CPP) $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CPP) -o $@ $(OBJ) $(LDFLAGS)
	cp libbass.dylib ..
	cp macbitch ..

clean:
	rm -f *.o
	rm -f macbitch