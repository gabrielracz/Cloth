// class Mass;
class Controller;
class RopeSim;
class PhysicsObject;

class Model{
    public:
    std::vector<PhysicsObject*> objects;
    PhysicsObject* grabbed;
    // RopeSim* rope;
    bool grabbing;
    bool cutting;
    int width;
    int height;
    Controller* ctrl;


    Model(Controller* initCtrl);
    ~Model();
    void AddObject(PhysicsObject* obj);
    void Step(float dt);
    void Step(Vector2D hitbox, int m, float dt);
    void Draw();
    void RebuildObjects();
    void ClearObjects();
    std::vector<PhysicsObject*>* GetObjects();
};