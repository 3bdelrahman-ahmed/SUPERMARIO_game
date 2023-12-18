struct color {
    float red;
    float green;
    float blue;
};

struct point {
    float x;
    float y;
};

struct block {
    bool IsPrimary;
    point topLeft;
    point bottomLeft;
    point topRight;
    point bottomRight;
};

struct character {
    float helath = 200;
};