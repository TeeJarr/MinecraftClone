//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_BLOCK_HPP
#define MINECRAFTCLONE_BLOCK_HPP
#include <raylib.h>
#include <sys/_types/_u_int8_t.h>
#include <array>

enum BlockIds {
    Bedrock,
    Air,
    Grass,
    Dirt,
    Stone,
    Water,
    OakWood,
    OakLeaves
};

struct Block {
    Vector3 position{};
    Vector3 size = {1,1,1};
    u_int8_t blockId{};
    Color color{};

    bool operator!() const {
        return blockId;
    }
};

inline Block BEDROCK_BLOCK{
    {},
    {1,1,1},
    Bedrock,
    BLACK
};

inline Block GRASS_BLOCK{
    {},
    {1,1,1},
    Grass,
    GREEN
};

inline Block DIRT_BLOCK{
    {},
    {1,1,1},
    Dirt,
    BROWN
};

inline Block WATER_BLOCK{
    {},
    {1,1,1},
    Water,
    BLUE
};

inline Block STONE_BLOCK{
    {},
    {1,1,1},
    Stone,
    GRAY
};

inline Block AIR_BLOCK{
    {},
    {1,1,1},
    Air,
    WHITE
};



#endif //MINECRAFTCLONE_BLOCK_HPP