//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_BLOCK_HPP
#define MINECRAFTCLONE_BLOCK_HPP
#include <raylib.h>
#include <sys/_types/_u_int8_t.h>
#include <array>

enum BlockIds {
    Air,
    Grass,
    Dirt,
    Water,
    OakWood,
    OakLeaves
};

struct Block {
    Vector3 position{};
    Vector3 size = {1,1,1};
    Color color{};
    u_int8_t blockId{};
};

#endif //MINECRAFTCLONE_BLOCK_HPP