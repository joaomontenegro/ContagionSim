#include "window.h"
#include "log.h"

#include <chrono>
#include <iostream>

GLWindow::GLWindow(const std::string& title,
				   int width, int height,
				   GLRenderer* renderer)
	: _width(width)
	, _height(height)
	, _renderer(renderer)
{
	// Create the Sdl Window
	_sdlWindow = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_OPENGL);
	if (!_sdlWindow) {
		Log::error("Failed to create window: " + title + " : " + SDL_GetError());
		return;
	}

	//TODO create this in the GLRenderer so that it can use sdl drawing there
	// Create the Sdl Renderer
	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
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

	// Create the GL context
	_glContext = new SDL_GLContext(SDL_GL_CreateContext(_sdlWindow));

	// Set window title
	SDL_SetWindowTitle(_sdlWindow, title.c_str());
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

void GLWindow::draw()
{
	_renderer->render(_sdlRenderer);
	_prevDrawTime = SDL_GetTicks();
}

size_t GLWindow::getTimeSinceLastDraw() {
	return SDL_GetTicks() - _prevDrawTime;
}
