#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point
{
    public:
        Point(int x, int y);
        ~Point();
        int getX() const { return x; }
        int getY() const { return y; }
        friend ostream& operator <<(ostream& out, const Point &b);

    protected:

    private:
        int x;
        int y;
};

#endif // POINT_H
