#include<math.h>
#include"spring.hpp"

class RopeSim
{
public:
    float dt;
    float k;
    float springlength;
    std::vector<Mass*> anchors;
    std::vector<Mass*> masses;
    std::vector<Spring*> springs;

    RopeSim(int masscount, int width, float totalmass, float x, float y, float dt, float k);
    
    static void getGridPos(int index, int width, int* x, int* y);
    void buildCloth(float startx, float starty, int masscount, float pointMass);
    void buildString(float x, float y, int masscount, float springlength, float pointMass);
    void update();
    void update(bool cutting, Vector2D mousepos);
    void render(sf::RenderWindow *window);
    void addMass(float x, float y, float mass);
    void addSpring(int i1, int i2, float kc);
    void free();
};