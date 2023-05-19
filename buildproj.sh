#!/bin/bash

cd build && \
make clean && \
cmake -G "Unix Makefiles" .. && \

make -j2 && \
chmod +x safe_c && \
./safe_c && \
cd .. \
