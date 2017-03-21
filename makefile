CC = g++
#CC = clang
FLAGS = -std=c++1y -Wall -pedantic -g
CPP_FILES := $(wildcard src/*.cpp)
#SDL_DIR = "include/SDL2-2.0.4/i686-w64-mingw32"
#SDL_IMG_DIR = "include/SDL2_image-2.0.1/i686-w64-mingw32"
#SDL_TTF_DIR = "include/SDL2_ttf-2.0.14/i686-w64-mingw32"
#SDL_MIXER_DIR = "include/SDL2_mixer-2.0.1/i686-w64-mingw32"
#INCLUDES = -I $(SDL_DIR)"/include" -I$(SDL_IMG_DIR)"/include" -I $(SDL_TTF_DIR)"/include" -I$(SDL_MIXER_DIR)"/include"
#LIBRARIES = -L $(SDL_DIR)"/lib/x64" -L $(SDL_IMG_DIR)"/lib" -L$(SDL_TTF_DIR)"/lib" -L$(SDL_MIXER_DIR)"/lib"
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
build/main.exe: $(OBJ_FILES)
	$(CC) $(FLAGS) -o $@ $^ $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
clean:
	rm -f obj/*.o *.out
