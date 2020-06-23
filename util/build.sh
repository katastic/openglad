#gcc scenver.c -lSDL -I/usr/include/SDL -o scenver
#gcc pixieread.c -lSDL -I/usr/include/SDL -o pixieread
#gcc pixedit.c -lSDL -I/usr/include/SDL -o pixedit
#gcc getcolors.c -lSDL  -I/usr/include/SDL -o getcolors
#gcc savepng.c -lSDL2main    -lSDL2  -lSDL2_mixer -lpng16  -I/usr/include/SDL -o savepng

# this uses SDL 1?!?!?!
g++  pixconvert.cpp savepng.c -I/usr/include/SDL  -D_GNU_SOURCE=1 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL -lSDLmain -lSDL_image -lpng  -o pixconvert
#g++ colorview.cpp -lSDL -lSDLimage -lpng16  -I/usr/include/SDL -o colorview


