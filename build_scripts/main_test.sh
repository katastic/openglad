LD_RUN_PATH='./build_deps/' g++   -g    ../src/*.cpp    -I/usr/include/SDL2    -I../src/external/yam/    -I../src/external/libzip/    -I../src/external/libyaml/include/            -I../src/external/physfs/            -I../src/external/physfs/extras/            -I../src/external/physfs/extras/zlib123/            -I../src/external/micropather/            -L../build_deps/            -lcdeps    -lcppdeps    -lSDL2main    -lSDL2  -lSDL2_mixer -lpng16    -o    ../opengladvs   && echo -e "\n\nSUCCESS"
#  -lopengl32 


#LD_RUN_PATH='.' tells the linker that we'll have shared libraries located in our game run directory/build_deps, and to search there instead of forcing us to install our shared libs into system. Since they're not really shared libs.

#https://aimlesslygoingforward.com/blog/2014/01/19/bundling-shared-libraries-on-linux/
