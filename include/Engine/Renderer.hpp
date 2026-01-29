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

     static void drawBlock(const Block& block);
};


#endif //MINECRAFTCLONE_RENDERER_HPP