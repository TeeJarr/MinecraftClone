//
// Created by Tristan on 1/28/26.
//

#include "../../include/Engine/Renderer.hpp"
#include "../../include/World/Block.hpp"

#include <print>
#include <raylib.h>
#include <raymath.h>


std::vector<float> vertices;
std::vector<float> normals;
std::vector<unsigned short> indices;
std::vector<Color> colors;


void Renderer::drawBlock(const Block& block, const Camera3D& camera) {
    DrawCubeV(block.position, block.size, block.color);
}

Color Renderer::getBlockColor(const int blockId) {
    switch (blockId) {
        case Bedrock:
            return BLACK;
        case Stone:
            return GRAY;
        case Dirt:
            return BROWN;
        case Grass:
            return GREEN;
        default:
            return WHITE;
    }
}

bool Renderer::isBlockVisible(const Vector3& blockPosition, const Camera3D& camera) {
    Vector2 blockScreenPosition = GetWorldToScreen(blockPosition, camera);
    if (blockScreenPosition.x > static_cast<float>(GetScreenWidth()) ||
        blockScreenPosition.y > static_cast<float>(GetScreenHeight()) ||
        blockScreenPosition.x < 0 || blockScreenPosition.y < 0) {
        return false;
    } else {
    return true;
    }
}


void Renderer::drawChunk(const Chunk& chunk, const Camera3D &camera3d) {
    if (!chunk.meshBuilt) return;
    DrawModel(chunk.model, chunk.chunkPosition, 1.0f, WHITE);
}

Plane Renderer::normalizePlane(const Plane &plane) {
    float len = Vector3Length(plane.normal);
    return Plane(Vector3Scale(plane.normal, 1.0f / len),plane.distance / len);
}

void Renderer::getCameraFrustumPlanes(Frustrum &frustum, const Camera3D &camera) {
    Matrix view = GetCameraMatrix(camera);
    Matrix proj = MatrixPerspective(camera.fovy * DEG2RAD,
        (float)GetScreenWidth() / (float)GetScreenHeight(),
        0.1f,
        1000.0f
        );
    Matrix clip = MatrixMultiply(view, proj);

    frustum.leftFace = normalizePlane({
        {clip.m3 + clip.m0, clip.m7 + clip.m4, clip.m11 + clip.m8},
            clip.m15 - clip.m12
    });

    frustum.rightFace = normalizePlane({
        { clip.m3 - clip.m0, clip.m7 - clip.m4, clip.m11 - clip.m8 },
            clip.m15 - clip.m12
    });

    frustum.bottomFace = normalizePlane({
       { clip.m3 + clip.m1, clip.m7 + clip.m5, clip.m11 + clip.m9 },
       clip.m15 + clip.m13
   });

    // Top
    frustum.topFace = normalizePlane({
        { clip.m3 - clip.m1, clip.m7 - clip.m5, clip.m11 - clip.m9 },
        clip.m15 - clip.m13
    });

    // Near
    frustum.nearFace = normalizePlane({
        { clip.m3 + clip.m2, clip.m7 + clip.m6, clip.m11 + clip.m10 },
        clip.m15 + clip.m14
    });

    // Far
    frustum.farFace = normalizePlane({
        { clip.m3 - clip.m2, clip.m7 - clip.m6, clip.m11 - clip.m10 },
        clip.m15 - clip.m14
    });
}

bool Renderer::isBoxInFrustum(const BoundingBox &box,const Camera3D &camera_3d) {
    Frustrum frustum;
    getCameraFrustumPlanes(frustum, camera_3d);

    Plane planes[6] = { frustum.rightFace, frustum.leftFace, frustum.bottomFace, frustum.topFace, frustum.nearFace, frustum.farFace};

    for (const Plane& plane : planes) {
        Vector3 positive = {
            (plane.normal.x >= 0) ? box.max.x : box.min.x,
            (plane.normal.y >= 0) ? box.max.y : box.min.y,
            (plane.normal.z >= 0) ? box.max.z : box.min.z
        };

        float distance =
            Vector3DotProduct(plane.normal, positive) + plane.distance;

        if (distance < 0) {
            return false; // completely outside
        }
    }
    return true;
}

bool Renderer::isFaceExposed(const Chunk& chunk, int x, int y, int z, int face) {
    int nx = x + dx[face];
    int ny = y + dy[face];
    int nz = z + dz[face];

    // Outside chunk = exposed
    if (nx < 0 || nx >= CHUNK_SIZE_X ||
        ny < 0 || ny >= CHUNK_SIZE_Y ||
        nz < 0 || nz >= CHUNK_SIZE_Z)
        return true;

    // Neighbor is air → exposed
    return chunk.blocks[nx][ny][nz].blockId == BlockIds::Air;
}

void Renderer::buildMesh(const Chunk* chunk) {
    vertices.clear();
    normals.clear();
    indices.clear();

    int indexOffset = 0;

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {

                if (chunk->blocks[x][y][z].blockId == BlockIds::Air)
                    continue;

                Vector3 blockPos = {(float)x,(float)y,(float)z};



                for (int f = 0; f < 6; f++) {
                    if (!isFaceExposed(*chunk, x, y, z, (Face)f))
                        continue;


                    // Add 4 vertices
                    for (int v = 0; v < 4; v++) {
                        Color blockColor = getBlockColor(chunk->blocks[x][y][z].blockId);
                        Vector3 pos = Vector3Add(blockPos, FACE_VERTS[f][v]);
                        vertices.insert(vertices.end(), {
                            pos.x, pos.y, pos.z
                        });
                        normals.insert(normals.end(), {
                            FACE_NORMALS[f].x,
                            FACE_NORMALS[f].y,
                            FACE_NORMALS[f].z
                        });
                        colors.push_back(blockColor); // <-- per-vertex color
                    }

                    // Two triangles
                    indices.insert(indices.end(), {
                        (unsigned short)(indexOffset + 0),
                        (unsigned short)(indexOffset + 1),
                        (unsigned short)(indexOffset + 2),
                        (unsigned short)(indexOffset + 0),
                        (unsigned short)(indexOffset + 2),
                        (unsigned short)(indexOffset + 3)
                    });

                    indexOffset += 4;
                }
            }
        }
    }

    uploadMesh(chunk);
}

void Renderer::uploadMesh(const Chunk* chunk) {
    Mesh& mesh = chunk->mesh;
    mesh.vertexCount = vertices.size() / 3;
    mesh.triangleCount = indices.size() / 3;



    mesh.vertices = (float*)MemAlloc(vertices.size() * sizeof(float));
    mesh.normals  = (float*)MemAlloc(normals.size() * sizeof(float));
    mesh.indices  = (unsigned short*)MemAlloc(indices.size() * sizeof(unsigned short));
    mesh.colors = (unsigned char*)MemAlloc(colors.size() * sizeof(Color));

    memcpy(mesh.colors, colors.data(), colors.size() * sizeof(Color));
    memcpy(mesh.vertices, vertices.data(), vertices.size() * sizeof(float));
    memcpy(mesh.normals,  normals.data(),  normals.size() * sizeof(float));
    memcpy(mesh.indices,  indices.data(),  indices.size() * sizeof(unsigned short));

    UploadMesh(&mesh, false);

    chunk->model = LoadModelFromMesh(mesh);
    chunk->meshBuilt = true;
}

