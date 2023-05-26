cd build
mingw32-make clean
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..

mingw32-make -j4
safe_c.exe -r
cd ..
cmd
