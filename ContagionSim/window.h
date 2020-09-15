#ifndef _GL_RENDERER_H_
#define _GL_RENDERER_H_

#include "renderer.h"

#include <SDL.h>
#include <SDL_opengl.h>

class GLWindow
{
public:
	GLWindow(const std::string& title, int width, int height, GLRenderer* renderer);
	virtual ~GLWindow();

	bool isValid();

	virtual bool processEvents();
	void draw();

private:
	void _initGL();

	int _width;
	int _height;

	SDL_Window*    _sdlWindow   = nullptr;
	SDL_Renderer*  _sdlRenderer = nullptr;
	SDL_GLContext* _glContext   = nullptr;
	GLRenderer*    _renderer    = nullptr;
};

#endif

