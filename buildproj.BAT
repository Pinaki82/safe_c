cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..

mingw32-make -j4
cmd
