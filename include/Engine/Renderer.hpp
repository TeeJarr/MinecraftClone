//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_RENDERER_HPP
#define MINECRAFTCLONE_RENDERER_HPP

#include "../../include/World/Block.hpp"

class Renderer {
    public:
    static Camera3D& getCamera() {
        static Camera3D camera;
        return camera;
    }

    static void drawBlock(const Block& block, const Vector3& playerPosition);
    static bool isBlockVisible(const Vector3& blockPosition, const Vector3& playerPosition);
};


#endif //MINECRAFTCLONE_RENDERER_HPP