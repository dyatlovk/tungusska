#ifndef TUNGUSSKA_SCENE_H
#define TUNGUSSKA_SCENE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "Mesh.h"

class Scene {
	
public:
    Scene(const char* filename);
    ~Scene();

    /**
     * Render all meshes
     */
    void render();

private:
    std::string sMeshPath;

    // Mesh transform array
	// +---------+-----------+-----------+-----------+
	// |         |     X     |     Y     |     Z     |
	// +---------+-----------+-----------+-----------+
	// | transl0 | val[0][0] | val[0][1] | val[0][2] |
	// | transl1 | val[1][0] | val[1][1] | val[1][2] |
	// | ...     | ...       | ...       | ...       |
	// +---------+-----------+-----------+-----------+
	std::vector<std::vector<int> > fMeshTranslate;
	std::vector<std::vector<int> > fMeshRotate;
	
	CVar mCVar;
};

#endif //TUNGUSSKA_SCENE_H