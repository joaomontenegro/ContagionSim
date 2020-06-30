#ifndef _ARENA_H_
#define _ARENA_H_

#include "factory.h"

class Arena
{
public:
	Arena(float w, float h)  : width(w) , height(h) {}

	float width;
	float height;
};

class MyArena : public Arena
{
public:
	MyArena() : Arena(500, 500) {}
	virtual ~MyArena() = default;
};

/*
namespace {
	RegisterEntity<Arena, MyArena> _myArena("MyArena");
};
*/

#endif // _ARENA_H_
