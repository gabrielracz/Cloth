#include<SFML/Graphics.hpp>
// class Controller;

class View {
    public:
    Controller* ctrl;
    sf::RenderWindow* window;
    int width;
    int height;

    View(int initWidth, int initHeight, Controller* initCtrl);
    ~View(); 
    void InitWindow();
    void Update();
    void Draw();
    void PollEvents();
    Vector2D GetMousePos();
};