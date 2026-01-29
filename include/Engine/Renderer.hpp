//
// Created by Tristan on 1/28/26.
//

#ifndef MINECRAFTCLONE_RENDERER_HPP
#define MINECRAFTCLONE_RENDERER_HPP

#include "../../include/World/Block.hpp"
#include "World/Chunk.hpp"

enum Face {
    FACE_LEFT,
    FACE_RIGHT,
    FACE_BOTTOM,
    FACE_TOP,
    FACE_BACK,
    FACE_FRONT
};

constexpr Vector3 FACE_NORMALS[6] = {
    { -1,  0,  0 }, // LEFT
    {  1,  0,  0 }, // RIGHT
    {  0, -1,  0 }, // BOTTOM
    {  0,  1,  0 }, // TOP
    {  0,  0, -1 }, // BACK
    {  0,  0,  1 }  // FRONT
};

constexpr Vector3 FACE_VERTS[6][4] = {
    // LEFT (-X)
    { {0,0,1}, {0,1,1}, {0,1,0}, {0,0,0} },
    // RIGHT (+X)
    { {1,0,0}, {1,1,0}, {1,1,1}, {1,0,1} },
    // BOTTOM (-Y)
    { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1} },
    // TOP (+Y)
    { {0,1,1}, {1,1,1}, {1,1,0}, {0,1,0} },
    // BACK (-Z)
    { {1,0,1}, {1,1,1}, {0,1,1}, {0,0,1} },
    // FRONT (+Z)
    { {0,0,0}, {0,1,0}, {1,1,0}, {1,0,0} }
};

constexpr int dx[6] = { -1,  1,  0,  0,  0,  0 };
constexpr int dy[6] = {  0,  0, -1,  1,  0,  0 };
constexpr int dz[6] = {  0,  0,  0,  0, -1,  1 };


struct Plane {
    Vector3 normal;
    float distance;
};

struct Frustrum {
    Plane leftFace;
    Plane rightFace;

    Plane topFace;
    Plane bottomFace;

    Plane farFace;
    Plane nearFace;
};

class Renderer {
    public:
    static Camera3D& getCamera() {
        static Camera3D camera;
        return camera;
    }

    static void drawBlock(const Block &block, const Camera3D &camera);

    static Color getBlockColor(int blockId);

    static bool isBlockVisible(const Vector3 &blockPosition, const Camera3D &camera);

    static void drawChunk(const Chunk &chunk, const Camera3D &camera);

    static Plane normalizePlane(const Plane &plane);

    static void getCameraFrustumPlanes(Frustrum &frustum, const Camera3D &camera);

    static bool isBoxInFrustum(const BoundingBox &box, const Camera3D &camera_3d);

    static bool isFaceExposed(const Chunk &chunk, int x, int y, int z, int face);

    static void uploadMesh(const Chunk *chunk);

    static void buildMesh(const Chunk *chunk);
};


#endif //MINECRAFTCLONE_RENDERER_HPP