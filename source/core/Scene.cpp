//
// Created by Darryl Gouder on 25/12/2017.
//

#include "Scene.h"
#include "Sphere.h"

using namespace Solstice;

void Scene::BuildFloorScene()
{
    list.list.push_back(std::make_unique<Sphere>(Vector3(0, -1000, -6), 1000));
}

bool Scene::Intersect(const Ray& r, HitRecord& record)
{
    return list.hit(r, 0.0000001, Maths::Infinity, record);
}
