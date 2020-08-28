#include "window.h"
#include "log.h"

GLWindow::GLWindow(const std::string& title,
				   int width, int height,
				   GLRenderer* renderer)
	: _width(width)
	, _height(height)
	, _renderer(renderer)
{
	// Create the Sdl Window
	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL,
							    &_sdlWindow, &_sdlRenderer);
	if (!_sdlWindow) {
		Log::error("Failed to create window: " + title + " : " + SDL_GetError());
		return;
	}

	// Create the Sdl Renderer
	if (!_sdlRenderer) {
		Log::error("Failed to create renderer for: " + title + " : " + SDL_GetError());
		return;
	}

	// Check that we have OpenGL
	SDL_RendererInfo info;
	SDL_GetRendererInfo(_sdlRenderer, &info);
	if ((info.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(info.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		Log::error("No OpenGL for: " + title + " : " + SDL_GetError());
		return;
	}

	_glContext = new SDL_GLContext(SDL_GL_CreateContext(_sdlWindow));

	// Set window title
	SDL_SetWindowTitle(_sdlWindow, title.c_str());

	_initGL();
}

GLWindow::~GLWindow()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyRenderer(_sdlRenderer);
	SDL_DestroyWindow(_sdlWindow);
	
	delete _glContext;
}

bool GLWindow::isValid()
{
	return _sdlWindow && _sdlRenderer && _renderer && _glContext;
}

void GLWindow::show()
{
	while (true)
	{
		if (!processEvents()) { break; }
		draw();
	}
}

bool GLWindow::processEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

#include <iostream>

int counter = 0;

void GLWindow::draw()
{
	SDL_GL_MakeCurrent(_sdlWindow, *_glContext);
	_renderer->render();
	
	// TODO TOO SLOWWWWWW
	SDL_GL_SwapWindow(_sdlWindow);

	std::cout << counter++ << std::endl;
}


void GLWindow::_initGL()
{
	/* Our shading model--Gouraud (smooth). */
	glShadeModel(GL_SMOOTH);

	/* Culling. */
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	/* Set the clear color. */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* Setup our viewport. */
	glViewport(0, 0, _width, _height);

	/*
	 * Change to the projection matrix and set
	 * our viewing volume.
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	/* Ortho projection */
	glOrtho(0.f, (float)_width, (float)_height, 0.f, 0.f, 1.f);
}

