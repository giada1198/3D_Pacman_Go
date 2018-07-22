CC = g++
CFLAGS = -std=c++11 -Wall -framework OpenGL -framework Cocoa
MKFLAGS = mkdir -p
INC = -I include

all: src/main.cpp
	$(CC) $(INC) -c cocoa/fssimplewindowobjc.m -o build/fssimplewindowobjc.o
	$(CC) $(INC) -c cocoa/yssimplesound_macosx_objc.m -o build/yssimplesound_macosx_objc.o
	$(CC) $(CFLAGS) $(INC) src/*.cpp build/*.o -o exe.o
	$(MKFLAGS) bin/exe.app/Contents/MacOS
	mv exe.o bin/exe.app/Contents/MacOS/.
	bin/exe.app/Contents/MacOS/exe.o

clean:
	rm -f build/*.o
	rm -rf build/*.dSYM


