#!/bin/bash
pushd src
g++ -Wall -lsfml-graphics -lsfml-window -lsfml-system main.cpp player.cpp -o ../bin/delta
popd
