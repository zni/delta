#!/bin/bash
pushd src
g++ -Wall -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system main.cpp player.cpp bullet.cpp enemies.cpp -o ../bin/delta
popd
