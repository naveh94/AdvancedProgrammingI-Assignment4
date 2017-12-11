/*
 * Point.h
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

class Point {
public:
	Point(int x, int y) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x;
	int y;
};

#endif /* SRC_POINT_H_ */
