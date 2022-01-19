#include"rope.hpp"

class Cloth : public Rope {
public:
    void Build();
    Cloth(int masscount, int width, float totalmass, float x, float y, float k);
    // ~Cloth();
};