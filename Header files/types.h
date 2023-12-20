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
    float y = 50;
    bool isJumping = 0;
    bool isCrashed = false;
};

struct coin {
    float x;
    float y;
    bool isCollected = false;
};

struct obstacle {
    float x = 850;
    float y;
    bool isShape1 = 1;
};