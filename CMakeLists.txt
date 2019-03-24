cmake_minimum_required(VERSION 3.9)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 11)

add_executable(TransazioniFinanziarie main.cpp ContoCorrente.cpp ContoCorrente.h Utenza.cpp Utenza.h Date.cpp Date.h FileMgr.cpp FileMgr.h)