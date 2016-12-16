OPTS = -Wall -g -std=c++14
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

evosim: evosim.o animal.o plant.o
	g++ $(OPTS) -o evosim evosim.o animal.o plant.o $(LIBS) -Wno-deprecated

evosim.o: evosim.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c evosim.cpp

plant.o:  plant.cpp plant.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c plant.cpp

animal.o:  animal.cpp animal.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c animal.cpp

clean:
	rm -f *.o evosim

# OS X
ifeq "$(OSTYPE)" "darwin"
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
endif