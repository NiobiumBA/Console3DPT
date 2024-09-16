#include "PathTracing.h"

Eigen::Vector3f Graphics::PathTracing::Reflect(const Vector3f& vec, const Vector3f& normal)
{
    return vec - 2 * vec.dot(normal) * normal;
}

bool Graphics::PathTracing::PathIntersect(const Ray& ray, const RenderObject::VectorObjects& objects, const RenderObject* excludeObject, float maxDistance,
                                            float& distance, Vector3f& normal, RenderObject*& hitObject)
{
    distance = maxDistance;

    float currentDistance;
    Vector3f currentNormal;

    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i] != excludeObject &&
            objects[i]->RayIntersect(ray, currentDistance, currentNormal) &&
            currentDistance < distance)
        {
            distance = currentDistance;
            normal = currentNormal;
            hitObject = objects[i];
        }
    }

    return distance != maxDistance;
}

Eigen::Vector3f Graphics::PathTracing::PathTrace(Ray ray, const RenderObject::VectorObjects& objects, float maxDistance, int maxReflections)
{
    Vector3f light = Vector3f::Zero(); // sum of lights
    Vector3f reflectivity = Vector3f::Ones();

    float distance;
    Vector3f normal;
    Material* material;
    Ray newRay{};
    RenderObject* lastObject = nullptr;

    Vector3f lightDir = Vector3f::Ones().normalized();

    Ray lightRay{Vector3f::Zero(), lightDir};

    for (int i = 0; i < maxReflections; i++)
    {
        if (PathIntersect(ray, objects, lastObject, maxDistance, distance, normal, /* out */ lastObject))
        {
            material = lastObject->material;

            newRay.origin = ray.origin + distance * ray.direction;
            newRay.direction = MathEigen::lerp(Reflect(ray.direction, normal), normal, material->roughness);
            newRay.direction.normalize();
            
            ray = newRay;
            
            light += reflectivity.cwiseProduct(material->emittance);
            reflectivity = reflectivity.cwiseProduct(material->reflectance);

            // Calculate shadows
            lightRay.origin = ray.origin + 0.1f * lightDir;
            
            RenderObject* _l;
            if (PathIntersect(lightRay, objects, nullptr, maxDistance, distance, normal, _l))
            {
                light = (light - Vector3f::Constant(0.25f));// .cwiseMax(Vector3f::Zero());
            }
        }
        else
        {
            Vector3f skyboxColor = MathEigen::lerp(Vector3f::Zero().eval(), Vector3f(1, 1, 2), 0.5f * ray.direction.y() + 0.25f);

            light += reflectivity.cwiseProduct(skyboxColor);
            break;
        }
    }
    
    return light;
}
