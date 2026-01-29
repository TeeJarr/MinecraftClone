//
// Created by Tristan on 1/29/26.
//

#ifndef MINECRAFTCLONE_CHUNK_HPP
#define MINECRAFTCLONE_CHUNK_HPP
#include "../../include/World/Block.hpp"
#include <vector>

#include "FastNoiseLite.h"

constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 256;
constexpr int CHUNK_SIZE_Z = 16;

class Chunk {
public:
    Chunk();
    static Chunk generateChunk(const Vector3 &chunkPosition);
    static std::vector<std::shared_ptr<Chunk>> chunks;
    void drawChunk(const Camera3D &camera3d) const;

public:
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
    Vector3 chunkPosition{};
    int chunkId{};
    BoundingBox boundingBox{};

    mutable Mesh mesh = { 0 };
    mutable Model model = { 0 };
    mutable bool meshBuilt = false;
private:

    static float getChunkHeight(const Vector2 &worldPosition);
    static FastNoiseLite noise;
};

static int chunkCount = 0;


#endif //MINECRAFTCLONE_CHUNK_HPP