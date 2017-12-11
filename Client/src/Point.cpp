#include "../include/Point.h"

Point::Point(int x, int y) : x(x), y(y)
{}

Point::~Point()
{}


ostream &operator <<(ostream &out, const Point &b)
{
    out << "(" << b.getX() << "," << b.getY() << ")";
    return out;
}
