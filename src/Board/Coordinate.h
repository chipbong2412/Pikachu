#ifndef COORDINATE_H
#define COORDINATE_H

// defining a vector to draw the path later on
struct Vector {
    int x;
    int y;

    bool operator==(const Vector &a) const { return (x == a.x && y == a.y); }

    bool operator!=(const Vector &a) const { return !(x == a.x && y == a.y); }
};

// defining a struct Coordinate for convenience
struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate &a) const {
        return (x == a.x && y == a.y);
    }

    bool operator!=(const Coordinate &a) const {
        return !(x == a.x && y == a.y);
    }

    Coordinate &operator=(const Coordinate &a) {
        x = a.x;
        y = a.y;
        return *this;
    }

    Coordinate operator+(const Coordinate &a) const {
        Coordinate result;
        result.x = x + a.x;
        result.y = y + a.y;

        return result;
    }

    Vector operator-(const Coordinate &a) const {
        Vector result;
        result.x = x - a.x;
        result.y = y - a.y;

        return result;
    }
};

#endif