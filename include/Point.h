#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point
{
    public:
        /** Default constructor */
        Point(int x, int y);
        /** Default destructor */
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
