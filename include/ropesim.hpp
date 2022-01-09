#include<vector>
class Mass;
class Spring;
class Vector2D;

class RopeSim{
public:
    std::vector<Mass*> anchors;
    std::vector<Mass*> masses;
    std::vector<Spring*> springs;
    float dt;
    float k;
    float springlength;
    int masscount;
    float pointmass;
    float startx;
    float starty;

    RopeSim(int masscount, int width, float totalmass, float x, float y, float k);
    ~RopeSim();

    //Overloads
    void Update(float dt);
    void Update(Vector2D hitbox, int m, float dt);
    std::vector<std::pair<Vector2D, Vector2D>>* Draw(); 

    static void getGridPos(int index, int width, int* x, int* y);
    void buildCloth();
    void buildString(float x, float y, int masscount, float springlength, float pointMass);
    void addMass(float x, float y, float mass);
    void addSpring(int i1, int i2, float kc);
    void rebuild();
    void free();
};