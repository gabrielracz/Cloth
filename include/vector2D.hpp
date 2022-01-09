class Vector2D{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    float getLength();
    float getDistance(Vector2D v);
    void print();
    

    Vector2D operator-(const Vector2D &other) const;
    Vector2D operator-(const float other) const;
    Vector2D operator-();
    Vector2D operator+(const Vector2D &other);
    Vector2D operator*(const float other);
    Vector2D operator/(const float other);
};