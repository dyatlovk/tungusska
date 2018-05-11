#ifndef TUNGUSSKA_GLRENDER_H
#define TUNGUSSKA_GLRENDER_H

#include <boost/log/trivial.hpp>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

class GLRender {
public: 
	GLRender();
	~GLRender();

	void setupRenderer(const char *title,
                int width,
                int height,
                int bpp,
                bool fullscreen);

	void destroyRender();
}

#endif