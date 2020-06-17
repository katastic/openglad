gcc -g ../src/external/libyaml/src/*.c ../src/external/libzip/*.c ../src/external/physfs/*.c  ../src/external/physfs/zlib123/*.c ../src/external/physfs/platform/*.c ../src/external/physfs/extras/*.c ../src/external/physfs/archivers/*.c  -I/usr/include/SDL2        -I../src/external/yam/	        -I../src/external/libzip/        -I../src/external/libyaml/include/	       -I../src/external/physfs/   	        -I../src/external/physfs/extras/  	        -I../src/external/physfs/extras/zlib123/	        -I../src/external/micropather/	  -shared -fPIC    -lSDL2	               -o ../build_deps/libcdeps.so  
#	&&  ar rcs ../build_deps/libcdeps.a ../build_deps/libcdeps.o && ranlib ../build_deps/libcdeps.a


# NOT a shared so no need for fPIC

#NOTE, these have to be copied into the main folder for opengladvs to see the shared lib. or find a way to embed it anyway