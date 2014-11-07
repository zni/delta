#!/bin/bash
pushd src
g++ -Wall -std=c++11 main.cpp player.cpp bullets.cpp enemies.cpp -o ../bin/delta -lsfml-graphics -lsfml-window -lsfml-system
popd
