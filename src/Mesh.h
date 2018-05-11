#ifndef TUNGUSSKA_MESH_H
#define TUNGUSSKA_MESH_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

#include "CVar.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "game.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

/**
 * Create mesh
 */
class Mesh
{
public :
    struct MeshEntry {
        enum BUFFERS {
            VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
        };
        GLuint vao;
        GLuint vbo[4];

        unsigned int elementCount;
        GLuint mShader;

        MeshEntry(aiMesh *mesh);
        ~MeshEntry();

        void load(aiMesh *mesh);
        void render();
    };

    std::vector<MeshEntry*> meshEntries;

public:
    Mesh(const char *filename);
    ~Mesh(void);

    /**
     * Mesh render
     */
    void render();

    /**
     * Set mesh translate
     * @param x float x
     * @param y float y
     * @param z float z
     */
    void translate(float x, float y, float z);

    /**
     * rotating mesh
     * @param yaw       float yaw
     * @param pitch     float pitch
     * @param roll      float roll
     */
    void rotate(float yaw, float pitch, float roll);
};

#endif
