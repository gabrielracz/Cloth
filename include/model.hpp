// class Mass;
class Controller;
class RopeSim;

class Model{
    public:
    std::vector<RopeSim*> objects;
    // RopeSim* rope;
    bool grabbing;
    bool cutting;
    int width;
    int height;
    Controller* ctrl;


    Model(Controller* initCtrl);
    ~Model();
    void AddObject(RopeSim* obj);
    void Step(float dt);
    void Step(Vector2D hitbox, int m, float dt);
    void Draw();
    std::vector<RopeSim*>* GetObjects();
    // void start();
    // void handle_events();
};