#include<SFML/Graphics.hpp>
#include"vector2D.hpp"

class Mass
{
public:
    float m;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    bool anchored;

    Mass(float x, float y, float mass);
    
    void draw(sf::RenderWindow *window);
    void solve(float dt);
    void applyForce(Vector2D &force, float dt);
    void move(float dt);
};