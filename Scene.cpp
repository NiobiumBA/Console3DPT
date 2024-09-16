#include "Scene.h"

Scene::Scene()
{
	if (current == nullptr)
		current = this;

	_objects = std::vector<Behaviour*>();
}

void Scene::Add(Behaviour& object)
{
	auto it = std::find(_objects.begin(), _objects.end(), &object);

	if (it != _objects.end())
		throw std::exception("Object has already added");

	_objects.push_back(&object);
	

	if (_isStarted)
	{
		object.OnEnable();
		object.Start();
	}
}

void Scene::Destroy(Behaviour& object)
{
	auto it = std::find(_objects.begin(), _objects.end(), &object);

	if (it == _objects.end())
		throw std::exception("Not found an object for destroying");

	object.OnDisable();
	object.OnDestroy();
	_objects.erase(it);
}

void Scene::Start()
{
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->GetEnabled())
		{
			_objects[i]->OnEnable();
			_objects[i]->Start();
		}
	
	_isStarted = true;
}

void Scene::Update()
{
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->GetEnabled())
			_objects[i]->Update();
}

const std::vector<Behaviour*>& Scene::GetObjects() const
{
	return _objects;
}
