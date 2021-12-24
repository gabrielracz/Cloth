#include"mass.hpp"
class Spring
{
public:
    Mass *mass1;
    Mass *mass2;
    float springConstant;
    float springlength;
    bool tear;

    Spring(Mass *mass1, Mass *mass2, float springConstant, float springlength);
    void solve(float dt);
    void move();
    void draw(sf::RenderWindow *window);
    bool check_collision(Vector2D comp);
    bool check_tear();

};