cmake_minimum_required(VERSION 3.9)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(test)

set(SOURCE_FILES main.cpp ContoCorrente.cpp ContoCorrente.h Utenza.cpp Utenza.h Date.cpp Date.h FileMgr.cpp FileMgr.h Transazione.h Transazione.cpp Prelievo.h Deposito.h DateTime.cpp DateTime.h Menu.cpp Bonifico.h Investimento.h Investimento.cpp Bonifico.cpp Prelievo.cpp Deposito.cpp)
add_executable(myExecutable ${SOURCE_FILES})
add_library(core ${SOURCE_FILES})
target_link_libraries(myExecutable core)