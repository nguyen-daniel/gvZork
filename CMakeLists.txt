cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Item.cpp
        Item.h
        NPC.cpp
        NPC.h
        Location.cpp
        Location.h
        Game.cpp
        Game.h
)
