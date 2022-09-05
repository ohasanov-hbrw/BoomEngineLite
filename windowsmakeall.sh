make clean
make deps CC="x86_64-w64-mingw32-gcc --static" -j12
make run CC="x86_64-w64-mingw32-g++ --static" name="BoomEngine.exe" ldflags="-Lvendor/raylib/src -lraylib -lpthread -lwinmm -lgdi32 -lopengl32" -j12