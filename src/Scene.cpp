#include <vector>

#include <vector>
#include "Mesh.h"
#include "Scene.h"

namespace pt = boost::property_tree;

// Meshes container
std::vector<Mesh* > mmesh;

/**
 * Scene constructor. Parse scene file and load objects
 */
Scene::Scene(const char* filename) {
    LOG_INFO << "Build world...";
    pt::ptree root;
    pt::read_json(filename, root);

    //parse scene section
    int index = 0;
    BOOST_FOREACH(pt::ptree::value_type& v, root.get_child( "scene" )) {
        // mesh
        std::string sMeshPath = root.get<std::string>("scene." + v.first + ".mesh");
        mmesh.push_back( new Mesh( sMeshPath.c_str() ) );

        // resizing transform data array for every iteration
        fMeshTranslate.resize(fMeshTranslate.size() + 1);
        for (unsigned int i = 0; i < fMeshTranslate.size(); ++i)
            fMeshTranslate[i].resize(3);
        fMeshRotate.resize(fMeshRotate.size() + 1);
        for (unsigned int i = 0; i < fMeshRotate.size(); ++i)
            fMeshRotate[i].resize(3);

        // translate
        fMeshTranslate[index][0] = root.get<float>("scene." + v.first + ".transform.translate.x");
        fMeshTranslate[index][1] = root.get<float>("scene." + v.first + ".transform.translate.y");
        fMeshTranslate[index][2] = root.get<float>("scene." + v.first + ".transform.translate.z");

        // rotate
        fMeshRotate[index][0] = root.get<float>("scene." + v.first + ".transform.rotate.yaw");
        fMeshRotate[index][1] = root.get<float>("scene." + v.first + ".transform.rotate.pitch");
        fMeshRotate[index][2] = root.get<float>("scene." + v.first + ".transform.rotate.roll");

        ++index;
    }
    
    sMeshPath.clear(); //tmp mesh var

    LOG_INFO << "Loaded objects: " << mmesh.size();

    mCVar.registerVar<int>("s_objects", 0, mmesh.size(), "Scene object counter");
};

/**
 * Clear scene
 */
Scene::~Scene() {
    for(unsigned int i = 0; i < mmesh.size(); ++i) {
        delete mmesh.at(i);
    }
    mmesh.clear();

    fMeshTranslate.resize(0);
    fMeshRotate.resize(0);

    mCVar.unregister( "s_objects" );
};

/**
 * Render all objects
 */
void Scene::render()
{
    // if(g_cvars.find("r_wireframe")->second == 1) {
    //     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // }
     for(unsigned int i = 0; i < mmesh.size(); ++i) {
        glPushMatrix();
        mmesh.at(i)->rotate(fMeshRotate[i][0],fMeshRotate[i][1],fMeshRotate[i][2]);
        mmesh.at(i)->translate(fMeshTranslate[i][0],fMeshTranslate[i][1],fMeshTranslate[i][2]);
        mmesh.at(i)->render();
        glPopMatrix();
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}