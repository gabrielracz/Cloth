#include<vector>
#include"physicsobject.hpp"
class Vector2D;

class Mass : PhysicsObject{
public:
    float m;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    bool anchored;
    bool grabbed;

    Mass(float x, float y, float mass);
    ~Mass() = default;
    
    void Solve(float dt);
    void Solve(Vector2D hitbox);
    void ApplyForce(Vector2D &force, float dt);
    bool CheckCollision(Vector2D hitbox);

    std::vector<std::pair<Vector2D, Vector2D>>* Draw();
    void Update(float dt);
    void Update(Vector2D mousepos, int m, float dt);

};