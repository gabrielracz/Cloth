#include<vector>
class View;
class Model;
class Vector2D;
class RopeSim;


class Controller {
public:
    View* view;
    Model* model;
    bool running;
    float dt;
    bool cutting;
    bool grabbing;

    Controller();

    Vector2D GetMousePos();
    std::vector<RopeSim*>* GetObjects();
    void Update();

    void HandleClosed();
    void HandleCutting(bool t);
    void HandleGrabbing(bool t);
    void HandleReload();
};