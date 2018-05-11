#include "CVar.h"
#include "Mesh.h"


/**
*   Constructor, loading the specified aiMesh
**/
Mesh::MeshEntry::MeshEntry(aiMesh *mesh) {
    vbo[VERTEX_BUFFER] = 0;
    vbo[TEXCOORD_BUFFER] = 0;
    vbo[NORMAL_BUFFER] = 0;
    vbo[INDEX_BUFFER] = 0;

    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    elementCount = mesh->mNumFaces * 3;

    if(mesh->HasPositions()) {
        float *vertices = new float[mesh->mNumVertices * 3];
        for(unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        glGenBuffers(1, &vbo[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        // glEnableVertexAttribArray (0);

        delete[] vertices;
    }
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
*   Deletes the allocated OpenGL buffers
**/
Mesh::MeshEntry::~MeshEntry() {
    if(vbo[VERTEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
    }

    if(vbo[TEXCOORD_BUFFER]) {
        glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
    }

    if(vbo[NORMAL_BUFFER]) {
        glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
    }

    if(vbo[INDEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
    }

    // glDeleteVertexArrays(1, &vao);
    
}

/**
*   Renders this MeshEntry
**/
void Mesh::MeshEntry::render() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
    glVertexPointer(3, GL_FLOAT, 0, (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, elementCount);
    glBindVertexArray(0);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
*   Mesh constructor, loads the specified filename if supported by Assimp
**/
Mesh::Mesh(const char* filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, 0);
    if(!scene) {
        LOG_ERROR << "Unable to load mesh: " << importer.GetErrorString();
    }
    LOG_DEBUG << " - Mesh: " << filename << " is loaded";

    for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        meshEntries.push_back(new Mesh::MeshEntry(scene->mMeshes[i]));
    }
}

/**
*   Clears all loaded MeshEntries
**/
Mesh::~Mesh(void)
{
    for(unsigned int i = 0; i < meshEntries.size(); ++i) {
        delete meshEntries.at(i);
    }
    meshEntries.clear();
}

/**
*   Renders all loaded MeshEntries
**/
void Mesh::render() {
    for(unsigned int i = 0; i < meshEntries.size(); ++i) {
        meshEntries.at(i)->render();
    }
}

/**
 * Set mesh translate
 * @param x float
 * @param y float
 * @param z float
 */
void Mesh::translate(float x, float y, float z)
{
    glTranslatef(x, y, z);
}

/**
 * rotating mesh
 * @param yaw       float yaw
 * @param pitch     float pitch
 * @param roll      float roll
 */
void Mesh::rotate(float yaw, float pitch, float roll)
{
    glRotatef(yaw, 1.0f, 0.0f, 0.0f);
    glRotatef(pitch, 0.0f, 1.0f, 0.0f);
    glRotatef(roll, 0.0f, 0.0f, 1.0f);
}