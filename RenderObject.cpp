#include "RenderObject.h"
#include "Scene.h"

std::vector<Graphics::PathTracing::RenderObject*>& Graphics::PathTracing::RenderObject::GetRenderObjects()
{
	return Scene::current->renderObjects;
}

void Graphics::PathTracing::RenderObject::OnEnable()
{
	Scene::current->renderObjects.push_back(this);
}

void Graphics::PathTracing::RenderObject::OnDisable()
{
	auto it = std::find(GetRenderObjects().begin(), GetRenderObjects().end(), this);

	GetRenderObjects().erase(it);
}
