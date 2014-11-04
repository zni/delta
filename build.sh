#!/bin/bash
pushd src
g++ -Wall -std=c++0x -lsfml-graphics -lsfml-window -lsfml-system main.cpp player.cpp bullet.cpp -o ../bin/delta
popd
