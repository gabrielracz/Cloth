#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <math.h>

class Vector2D
{
public:
    float x;
    float y;

    Vector2D(){
        this->x = 0;
        this->y = 0;
    }

    Vector2D(float x, float y){
        this->x = x;
        this->y = y;
    }

    float getLength(){
        return sqrt((x * x) + (y * y));
    }

    Vector2D operator-(const Vector2D &other) const{
        Vector2D v = Vector2D(x - other.x, y - other.y);
        return v;
    }

    Vector2D operator-(const float other) const{
        return Vector2D(x - other, y - other);
    }

    Vector2D operator-(){
        return Vector2D(-x, -y);
    }

    Vector2D operator+(const Vector2D &other){
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator*(const float other){
        return Vector2D(x * other, y * other);
    }

    Vector2D operator/(const float other){
        return Vector2D(x / other, y / other);
    }

    void print(){
        std::cout << "[ " << this->x << ", " << this->y << " ]\n";
    }
};

class Mass
{
public:
    float m;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    bool anchored;

    Mass(float x, float y, float mass){
        m = mass;
        position = Vector2D(x, y);
        // position = new Vector2D(x, y);
        // velocity = new Vector2D();
        // acceleration = new Vector2D();
        anchored = false;
    }

    void draw(sf::RenderWindow *window){
        // if (m > 3.0f)
        {
            float r = 2; //fmax(m/2, 2);
            sf::CircleShape circle(r);
            circle.setOrigin(r, r);
            circle.setPosition(sf::Vector2f(position.x, position.y));
            window->draw(circle);
        }
    }

    void solve(float dt){
        Vector2D gravity(0, 9.8 * m);
        Vector2D airResistance = velocity * -0.0075;
        Vector2D forceNet = gravity + airResistance;

        applyForce(forceNet, dt);
    }

    void applyForce(Vector2D &force, float dt){
        //a = F/m
        acceleration = force * 1 / m; //Acceleration due to current
        velocity = velocity + (acceleration * (dt));
    }

    void move(float dt){
        position = position + velocity * dt;
    }
};

class Spring
{
public:
    Mass *mass1;
    Mass *mass2;
    float springConstant;
    float springlength;

    Spring(Mass *mass1, Mass *mass2, float springConstant, float springlength){
        this->mass1 = mass1;
        this->mass2 = mass2;
        this->springConstant = springConstant;
        this->springlength = springlength;
    }

    void solve(float dt){
        // Fs = -k (x - l)
        // k = springConstant, x = positionDelta, l = springlength

        Vector2D deltaPos = mass1->position - mass2->position;
        float r = deltaPos.getLength();
        Vector2D springForce = (deltaPos / r) * (-(springlength - r)) * (-springConstant);
        Vector2D netForce = springForce + (-((mass1->velocity) - (mass2->velocity))) * 0.4;

        if (!mass1->anchored)
        {
            mass1->applyForce(netForce, dt);
            mass1->move(dt);
        }
        if (!mass2->anchored)
        {
            Vector2D oppForce = -netForce;
            mass2->applyForce(oppForce, dt);
            mass2->move(dt);
        }
    }

    void move(){
    }

    void draw(sf::RenderWindow *window){
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(mass1->position.x, mass1->position.y)),
            sf::Vertex(sf::Vector2f(mass2->position.x, mass2->position.y))};
        window->draw(line, 2, sf::Lines);
    }
};

class RopeSim
{
public:
    float dt;
    float k;
    float springlength;
    std::vector<Mass*> anchors;
    std::vector<Mass*> masses;
    std::vector<Spring*> springs;

    RopeSim(int masscount, int width, float totalmass, float x, float y, float dt, float k){
        this->dt = dt;
        this->k = k;
        this->springlength = width / masscount;
        
        // float pointMass = totalmass / (masscount * masscount);
        float pointMass = totalmass / masscount;

        buildCloth(x, y, masscount, pointMass);

        // buildString(x, y, masscount, springlength, pointMass);
        
    }

    static void getGridPos(int index, int width, int* x, int* y){
        *x = index % width;
        *y = floor(index / width);
    }

    void buildCloth(float startx, float starty, int masscount, float pointMass){
        //Start at top left corner
        //masscount will be a square piece of cloth
        int totalMasses = masscount * masscount;
        int mx, my;

        Mass* anchor = new Mass(startx, starty, pointMass);
        masses.push_back(anchor);
        anchors.push_back(anchor);
        anchor->anchored = true;

        for(int i = 1; i < totalMasses; i++){
            getGridPos(i, masscount, &mx, &my);
            // std::cout << springlength * mx + startx << " " << my * springlength + starty << '\n';                
            Mass *m = new Mass( springlength * mx + startx, my * springlength + starty, pointMass);
            masses.push_back(m);
            if(my == 0 && mx % (masscount/3) == 0){
                m->anchored = true;
                anchors.push_back(m);
            }
            m->position.x /= 1.1;
        }

        int maxy = my;
        float kscale;

        for(int i = 0; i < totalMasses; i++){
            getGridPos(i, masscount, &mx, &my);
            kscale = k  + k * (my/maxy);
            if(mx > 0){
                addSpring(i, i - 1, k);
                // if(my < masscount - 1)
                //     addSpring(i, i + masscount - 1, k);
            }
            if(mx < masscount - 1){
                addSpring(i, i + 1, k);
                // if(my < masscount - 1)
                //     addSpring(i, i + masscount + 1, k);
            }
            if(my > 0){
                addSpring(i, i - masscount, k);
            }
            if(my < masscount - 1){
                addSpring(i, i + masscount, k);
            }
        }
    }

    void buildString(float x, float y, int masscount, float springlength, float pointMass){
        Mass* anchor = new Mass(x, x, pointMass);
        masses.push_back(anchor);
        anchors.push_back(anchor);
        anchor->anchored = true;

        for (int i = 1; i < masscount; i++)
        {
            Mass *m = new Mass(springlength * i + x, y, pointMass);
            masses.push_back(m);
            Spring *s = new Spring(masses[i - 1], m, k, springlength);
            springs.push_back(s);
        }
    }

    void update(sf::RenderWindow *window){
        for (auto &s : springs)
        {
            s->solve(dt);
        }
        for (auto &m : masses)
        {
            m->solve(dt);
            // m->draw(window);
        }
        for (auto &s : springs)
        {
            s->draw(window);
        }
    }

    void addMass(float x, float y, float mass){
        Mass *m = new Mass(x, y, mass);
        masses.push_back(m);
        
    }

    void addSpring(int i1, int i2, float kc){
        Spring *s = new Spring(masses[i1], masses[i2], kc, springlength);
        springs.push_back(s);
    }

    void free(){
        for (auto &m : masses)
        {
            delete m;
        }
        for (auto &s : springs)
        {
            delete s;
        }
    }
};

int main(int argc, char *argv[]){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 1280), "Rope");
    window->clear(sf::Color(0, 0, 0, 255));
    window->display();

    float dt = 0.02f;
    //num, length, weight, x, y, dt, k
    RopeSim rope(100, 900, 20, 100, 100, dt, 40);
    
    // RopeSim rope(100, 600, 10, 480, 100, dt, 130);
    //rope.masses.back()->m = 1.5;

    bool toggle = false;
    usleep(500000);
    Mass* grabbed;
    while (window->isOpen())
    {
        sf::Event e;
        while (window->pollEvent(e))
        {
            if (e.type == e.Closed)
            {
                window->close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                toggle = !toggle;
                float leastdistance = 1000000000000.0;
                float distance;
                Vector2D mousepos (sf::Mouse::getPosition(*(window)).x, sf::Mouse::getPosition(*(window)).y);
                for(auto &m : rope.anchors){
                    distance = (m->position - mousepos).getLength();
                    if(distance < leastdistance){
                        leastdistance = distance;
                        grabbed = m;
                    }
                }
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    usleep(0.0015 * 1000000);
                }
            }
            if (toggle)
            {
                grabbed->position.x = sf::Mouse::getPosition(*(window)).x;
                grabbed->position.y = sf::Mouse::getPosition(*(window)).y;
            }
        }
        //usleep(0.0015 * 1000000);
        window->clear(sf::Color(0, 0, 0, 255));
        rope.update(window);
        window->display();
        // getchar();
        // char ch;
        // scanf("%c", &ch);
    }

    delete window;
    rope.free();
    return 0;
}
