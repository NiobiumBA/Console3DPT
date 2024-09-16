#include "SphereRender.h"

Graphics::PathTracing::SphereRender::SphereRender(const Vector3f& position, float radius, Material& mat)
    : position(position)
{
    material = &mat;
    SetRadius(radius);
}

void Graphics::PathTracing::SphereRender::SetRadius(float radius)
{
    _radius = std::max(radius, 0.0f);
}

float Graphics::PathTracing::SphereRender::GetRadius() const
{
    return _radius;
}

bool Graphics::PathTracing::SphereRender::RayIntersect(const Ray& ray, float& distance, Vector3f& normal) const
{
    Vector3f oc = ray.origin - position;
    float b = oc.dot(ray.direction);
    Vector3f qc = oc - b * ray.direction;
    float h = _radius * _radius - qc.dot(qc);
    
    if (h < 0.0) return false; // no intersection
    
    h = std::sqrt(h);
    
    float root1 = -b - h;
    float root2 = -b + h;
    
    if (root1 > 0)
        distance = root1;
    else if (root2 > 0)
        distance = root2;
    else
        return false;
    
    normal = ray.direction * distance + oc;
    normal.normalize();

    return true;
}
