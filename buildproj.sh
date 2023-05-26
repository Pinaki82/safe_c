#!/bin/bash

cd build && \
cmake -G "Unix Makefiles" .. && \
make clean && \

make -j2 && \
chmod +x safe_c && \
./safe_c -r && \
cd .. \
