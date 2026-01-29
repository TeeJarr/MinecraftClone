//
// Created by Tristan on 1/29/26.
//

#ifndef MINECRAFTCLONE_CHUNK_HPP
#define MINECRAFTCLONE_CHUNK_HPP
#include "../../include/World/Block.hpp"
#include "../Engine/Settings.hpp"
#include <vector>


class Chunk {
public:
    static Chunk generateChunk(Vector3 chunkPosition);
    static Settings settings;
    static std::vector<std::shared_ptr<Chunk>> chunks;

    std::vector<Block> blocks;
    Vector3 chunkPosition;
    int chunkId;

private:
    Chunk() {
        settings = Settings::getInstance();
    }

    static bool isChunkVisible(Vector3 chunkPosition);
};


#endif //MINECRAFTCLONE_CHUNK_HPP