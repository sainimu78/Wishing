#!/bin/bash
mkdir -p out
g++ -I./ -oout/a a.cpp Util/MyCmd.cpp
