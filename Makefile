CFLAGS=-g -p `sdl-config --libs --cflags`
GLADFILES=button.o effect.o game.o glad.o gladpack.o graphlib.o guy.o help.o intro.o living.o loader.o obmap.o pal32.o parse32.o picker.o pixie.o pixien.o radar.o screen.o smooth.o sound.o stats.o text.o treasure.o video.o view.o walker.o weap.o input.o
SCENFILES=scen.o effect.o game.o gladpack.o graphlib.o guy.o help.o intro.o living.o loader.o obmap.o pal32.o parse32.o pixie.o pixien.o radar.o screen.o smooth.o sound.o stats.o text.o treasure.o video.o view.o walker.o weap.o input.o


all: openglad openscen


openglad: $(GLADFILES)
	g++ $(CFLAGS) -o openglad $(GLADFILES)

openscen: $(SCENFILES)
	g++ $(CFLAGS) -DOPENSCEN -o openscen $(SCENFILES)

clean:
	rm -f *.o
	rm -f openglad
	rm -f openscen

.cpp.o:
	g++ -g -p -c $<
