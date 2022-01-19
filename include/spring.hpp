#include"physicsobject.hpp"
class Mass;
class Vector2D;

class Spring : PhysicsObject{
public:
    Mass *mass1;
    Mass *mass2;
    float springConstant;
    float springlength;
    bool tear;

    Spring(Mass *mass1, Mass *mass2, float springConstant, float springlength);
    ~Spring() = default;

    bool CheckCollision(Vector2D comp);
    bool CheckTear();
    
    //Inherited virtuals
    std::vector<std::pair<Vector2D, Vector2D>>* Draw();
    void Update(float dt);
    void Update(Vector2D mousepos, int m, float dt);

};