#ifndef _GL_RENDERER_H_
#define _GL_RENDERER_H_

class GLWindow
{
public:
	GLWindow() {}
	virtual ~GLWindow() {}

protected:
	virtual void draw() = 0;

};

#endif

