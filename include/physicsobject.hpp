#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include<vector>

class Vector2D;

class PhysicsObject {
    public:

    virtual ~PhysicsObject() = default;
    virtual void Update(float dt)=0;
    virtual void Update(Vector2D mousepos, int m, float dt)=0;
    virtual std::vector<std::pair<Vector2D, Vector2D>>* Draw()=0;

};

#endif