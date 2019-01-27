CXX=g++
CXXFLAGS=-g -Wall
OUTPUT=out
ASS=assignment-1

#INC=include
#OUT=out
#LIB=lib
#OBJ=$(BIN)/obj

libUnitLite.so:
	$(CXX) $(CXXFLAGS) -fPIC ./include/*.cpp -shared -Wl,-soname,libUnitLite.so -o ./lib/libUnitLite.so

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(ASS)/%TEST.cpp)
OBJECT_FILES = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
    rm -r -f $(BIN)
    @# ^^^ I don't recommend suppressing the echoing of the command using @

# http://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: build

$(EXECUTABLE_FILES): $(OBJECT_FILES)
    @$(CC) $(LDFLAGS) -o $@ $^
    @# ^^^ http://www.gnu.org/software/make/manual/make.html#Automatic-Variables
    @echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
    @echo Compiling $<
    @# ^^^ Your terminology is weird: you "compile a .cpp file" to create a .o file.
    @mkdir -p $(@D)
    @# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
    @$(CC) $(CFLAGS) -o $@ $<
    @# ^^^ Use $(CFLAGS), not $(LDFLAGS), when compiling.


# https://codereview.stackexchange.com/questions/74136/makefile-that-places-object-files-into-an-alternate-directory-bin
