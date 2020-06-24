SRC_DIR := ../src
OBJ_DIR := ../obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS  := -Wl,--copy-dt-needed-entries -L../build_deps/ -lSDL2_mixer -lSDL2main -lSDL2   -lpng16   
CPPFLAGS :=   
CXXFLAGS := -I/usr/include/SDL2    -I../src/external/yam/    -I../src/external/libzip/    -I../src/external/libyaml/include/            -I../src/external/physfs/   -I../src/external/physfs/extras/  -I../src/external/physfs/extras/zlib123/  -I../src/external/micropather/  


# -Wl,--copy-dt-needed-entries
# https://stackoverflow.com/questions/19901934/libpthread-so-0-error-adding-symbols-dso-missing-from-command-line#:~:text=The%20DSO%20missing%20from%20command,a%20directly%20specified%20dynamic%20library.

#LD_RUN_PATH='./build_deps/' g++   -g    ../src/*.cpp    -I/usr/include/SDL2    -I../src/external/yam/    -I../src/external/libzip/    -I../src/external/libyaml/include/            -I../src/external/physfs/            -I../src/external/physfs/extras/            -I../src/external/physfs/extras/zlib123/            -I../src/external/micropather/            -L../build_deps/            -lcdeps    -lcppdeps    -lSDL2main    -lSDL2  -lSDL2_mixer -lpng16    -o    ../opengladvs   && echo -e "\n\nSUCCESS"

#LD_RUN_PATH='.' tells the linker that we'll have shared libraries located in our game run directory/build_deps, and to search there instead of forcing us to install our shared libs into system. Since they're not really shared libs.
#https://aimlesslygoingforward.com/blog/2014/01/19/bundling-shared-libraries-on-linux/

#FILES := ../obj/button.o ../obj/glad.o ../obj/guy.o ../obj/io.o ../obj/living.o ../obj/picker.o ../obj/radar.o ../obj/screen.o ../obj/text.o ../obj/view.o ../obj/campaign_picker.o ../obj/gloader.o ../obj/help.o ../obj/level_data.o ../obj/obmap.o ../obj/pixie.o ../obj/results_screen.o ../obj/smooth.o ../obj/treasure.o ../obj/walker.o ../obj/effect.o ../obj/gparser.o ../obj/input.o ../obj/level_editor.o ../obj/OuyaController.o ../obj/pixie_data.o ../obj/sai2x.o ../obj/sound.o ../obj/util.o ../obj/weap.o ../obj/game.o ../obj/graphlib.o ../obj/intro.o ../obj/level_picker.o ../obj/pal32.o ../obj/pixien.o ../obj/save_data.o ../obj/stats.o ../obj/video.o  -o out1


opengladvs: $(OBJ_FILES)
#	g++ $(LDFLAGS)  -o $@ $^
	LD_RUN_PATH='./build_deps/' g++ -std=c++17 -D_REENTRANT -g $(CXXFLAGS) $(OBJ_FILES) ../build_deps/*.o $(LDFLAGS) -o ../openglad

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -D_REENTRANT -g $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
clean:	
	rm -r ../obj/*
	rm ../openglad
	echo "DELETING OBJ files"
