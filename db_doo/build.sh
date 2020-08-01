#!/bin/sh
gcc -c sqlite3.c
g++ sqlite_world.cpp sqlite3.o -o sqlite_world