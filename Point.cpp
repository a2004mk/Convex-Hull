// Point.cpp
#include "Point.h"
#include <algorithm>

const float WORK_AREA_MIN_X = 50.0f;
const float WORK_AREA_MAX_X = 1150.0f;
const float WORK_AREA_MIN_Y = 150.0f;
const float WORK_AREA_MAX_Y = 750.0f;

Point::Point(float x, float y) : x(x), y(y) {}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

void clampPoint(Point& point) {
    if (point.x < WORK_AREA_MIN_X) point.x = WORK_AREA_MIN_X;
    if (point.x > WORK_AREA_MAX_X) point.x = WORK_AREA_MAX_X;
    if (point.y < WORK_AREA_MIN_Y) point.y = WORK_AREA_MIN_Y;
    if (point.y > WORK_AREA_MAX_Y) point.y = WORK_AREA_MAX_Y;
}

float orientation(const Point& pivot, const Point& p, const Point& q) {
    return (p.y - pivot.y) * (q.x - p.x) - (p.x - pivot.x) * (q.y - p.y);
}

float distSq(const Point& pivot, const Point& p) {
    float dx = p.x - pivot.x;
    float dy = p.y - pivot.y;
    return dx * dx + dy * dy;
}