//
// Created by Tristan on 1/29/26.
//

#include "../../include/World/Chunk.hpp"
#include "FastNoiseLite.h"
#include "Engine/Renderer.hpp"

FastNoiseLite Chunk::noise;

Chunk::Chunk() {
    noise.SetSeed(1337);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
}

float Chunk::getChunkHeight(const Vector2& worldPosition) {
    float scale = 0.1f;
    float height = noise.GetNoise(
        worldPosition.x * scale,
        worldPosition.y * scale
    );

    // Normalize from [-1,1] → [0,1]
    height = (height + 1.0f) * 0.5f;

    return height * 64.0f + 64.0f; // terrain range
}

Chunk Chunk::generateChunk(const Vector3& chunkPosition) {
    auto chunk = Chunk();
    chunk.chunkPosition = chunkPosition;
    chunk.chunkId = chunkCount++;


    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            const float worldX =  (chunkPosition.x * CHUNK_SIZE_X + static_cast<float>(x));
            const float worldZ = (chunkPosition.z * CHUNK_SIZE_Z + static_cast<float>(z));

            const int height = static_cast<int>(getChunkHeight((Vector2){worldX, worldZ}));

            for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                if (y == 0) {
                    Block bedrock = BEDROCK_BLOCK;
                    bedrock.position = {worldX, static_cast<float>(y), worldZ};
                    chunk.blocks[x][y][z] = bedrock;
                }
                else if (y > height) {
                    Block air = AIR_BLOCK;
                    air.position = {worldX, static_cast<float>(y), worldZ};
                    chunk.blocks[x][y][z] = air;
                }
                else if (y == height) {
                    Block grass = GRASS_BLOCK;
                    grass.position = {worldX, static_cast<float>(y), worldZ};
                    chunk.blocks[x][y][z] = grass;
                }
                else if (y > height - 4) {
                    Block dirt = DIRT_BLOCK;
                    dirt.position = {worldX, static_cast<float>(y), worldZ};
                    chunk.blocks[x][y][z] = dirt;
                }
                else {
                    Block stone = STONE_BLOCK;
                    stone.position = {worldX, static_cast<float>(y), worldZ};
                    chunk.blocks[x][y][z] = stone;
                }
            }
        }
    }
    chunk.boundingBox = {
        .min = {
            chunkPosition.x * CHUNK_SIZE_X,
            0.0f,
            chunkPosition.z * CHUNK_SIZE_Z
        },
        .max = {
            chunkPosition.x * CHUNK_SIZE_X + CHUNK_SIZE_X,
            CHUNK_SIZE_Y,
            chunkPosition.z * CHUNK_SIZE_Z + CHUNK_SIZE_Z
        }
    };

    Renderer::buildMesh(&chunk);
    return chunk;
}

void Chunk::drawChunk(const Camera3D &camera3d) const {
    if (!meshBuilt) return;
    DrawModel(model,
              {chunkPosition.x * CHUNK_SIZE_X, 0, chunkPosition.z * CHUNK_SIZE_Z},
              1.0f, WHITE);

    // if (Renderer::isBoxInFrustum(this->boundingBox, camera3d))
    //
    // for (const auto & x : blocks) {
    //     for (const auto & y : x) {
    //         for (const auto & block : y) {
    //             if (block.blockId == BlockIds::Air){
    //                 continue;
    //             }
    //             Renderer::drawBlock(block, camera3d);
    //         }
    //     }
    // }
}