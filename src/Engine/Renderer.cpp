//
// Created by Tristan on 1/28/26.
//

#include "../../include/Engine/Renderer.hpp"
#include "../../include/World/Block.hpp"

#include <raylib.h>

void Renderer::drawBlock(const Block& block) {
    DrawCube(block.position, 1.0f,1.0f,1.0f, block.color);
}
