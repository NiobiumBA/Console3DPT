#pragma once
#include <vector>
#include <algorithm>
#include "Behaviour.h"
#include "RenderObject.h"

class Scene
{
	//typedef Graphics::PathTracing::RenderObject RenderObject;

public:
	static inline Scene* current = nullptr;

	Graphics::PathTracing::RenderObject::VectorObjects renderObjects;
	
	Scene();

	void Add(Behaviour& object);
	void Destroy(Behaviour& object);
	void Start();
	void Update();
	const std::vector<Behaviour*>& GetObjects() const;

private:
	std::vector<Behaviour*> _objects;
	bool _isStarted = false;
};

