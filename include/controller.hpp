#include<vector>
class View;
class Model;
class Vector2D;
class PhysicsObject;


typedef enum INTERACTION_MODES {
    CUT,
    GRAB,
    HOLD
};

class Controller {
public:
    View* view;
    Model* model;
    bool running;
    float dt;
    bool cutting;
    bool grabbing;
    bool rope_toggle;

    Controller();

    Vector2D GetMousePos();
    std::vector<PhysicsObject*>* GetObjects();
    void Update();

    void HandleClosed();
    void HandleCutting(bool t);
    void HandleGrabbing(bool t);
    void HandleReload();
};