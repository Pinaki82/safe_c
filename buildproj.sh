#!/bin/bash

cd build && \
cmake -G "Unix Makefiles" .. && \

make -j2 \
