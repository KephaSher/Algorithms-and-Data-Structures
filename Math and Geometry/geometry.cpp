// All code for geometry
/*
- points
- lines
- segments
- corss, dot product
- area of polygon
- line, segment intersection
- point in polygon
*/

#include <bits/stdc++.h>
#define MX 1000
using namespace std;

const double eps = 1e-9;

struct Point {
    double x, y;
    
    Point () {}
    Point (double _x, double _y) {
        x = _x, y = _y;
    }
    
    bool operator<(const Point& p) const {
        return x < p.x - eps || (abs(x - p.x) < eps && y < p.y - eps);
    }

};

struct Line {
    double a, b, c;

    Line() {}
    Line(Point p, Point q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm() {
        double z = sqrt(a * a + b * b);
        if (abs(z) > eps) a /= z, b /= z, c /= z;
    }

    // distance from a point to this line
    double dist(Point p) {
        return a * p.x + b * p.y + c;
    }
};

struct Segment{
    Point p, q;

    Segment () {}
    Segment (Point _p, Point _q) {
        p = _p, q = _q;
    }
};

// cross product of (x1, y1) and (x2, y2). starts at origin (0, 0)
double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

// cross product of vector b and vector c, starting at point a
double cross(Point &a, Point &b, Point &c) {
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

// dot product of (x1, y1) and (x2, y2). starts at origin (0, 0)
double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

// dot product of vector b and vector c, starting at point a
double dot(Point &a, Point &b, Point &c) {
    return dot(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

// distance between 2 points
double dist(Point &a, Point &b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// determines whether the area of triangle ABC is +, -, or 0.
int get_sign(Point A, Point B, Point C)
{
    double area = cross(A, B, C);
    if (area > eps) return 1;
    if (area < -eps) return -1;
    return 0;
}

// P, X, Y are collinear. Check if P between X and Y.
bool between(Point P, Point X, Point Y)
{
    return ((X.x <= P.x && P.x <= Y.x) || (Y.x <= P.x && P.x <= X.x)) 
        && ((X.y <= P.y && P.y <= Y.y) || (Y.y <= P.y && P.y <= X.y));
}

// segment intersection
bool intersect(Segment s1, Segment s2)
{
    Point P = s1.p, Q = s1.q, X = s2.p, Y = s2.q;

    int signs[4] = {get_sign(P, X, Y), get_sign(Q, X, Y),
                    get_sign(X, P, Q), get_sign(Y, P, Q)};

    //     ---
    //  ---------   this is why we have to check not just the first 2.
    if (signs[0] == 0 && signs[1] == 0 && signs[2] == 0 && signs[3] == 0)
        return between(P, X, Y) || between(Q, X, Y) || between(X, P, Q) || between(Y, P, Q); // the last can be removed

    return signs[0] != signs[1] && signs[2] != signs[3];
}

// area of a polygon, may be negative 
double area(vector<Point> v) {
    int n = v.size();

    double area = 0;
    for (int i = 0, j = n - 1; i < n; i++) {
        area += det(v[j].x, v[j].y, v[i].x, v[i].y);
        j = i;
    }

    return area / 2.0; // area = 1/2 det(A)
}

// checks if a point is on a segment (a, b)
bool onSegment(Point p, Point a, Point b) {
    if (dist(p, a) < eps) return true;
    if (dist(p, b) < eps) return true;
    // cross < 0 means on the same line, dot < 0 means angle > 90 (p is in a, b)
    if (abs(cross(p, a, b)) < eps && dot(p, a, b) < 0) return true;
    return false;
}

// checks if a point is on the boundary of the polygon
bool onBoundary(Point p, vector<Point> v) {
    int n = v.size();
    for (int i = 0, j = n - 1; i < n; i++) {
        if (onSegment(p, v[i], v[j])) return true;
        j = i;
    }
    return 0;
}

// checks if a point is in the polygon
bool inPolygon(Point p, vector<Point> v) {
    bool ret = false;
    int n = v.size();

    for (int i = 0; i < n; i++) {
        Point a = v[i], b = v[(i + 1) % n];
        if ((a.y > p.y) ^ (b.y > p.y)) 
            if ((cross(a, p, b) < 0) ^ (b.y < a.y))
                ret = !ret;
    }

    return ret;
}

// Point in polygon 
/*
for (int i = 1; i <= M; i++) {
    int x, y; cin >> x >> y;
    if (onBoundary(Point(x, y), v)) cout << "BOUNDARY\n";
    else if (inPolygon(Point(x, y), v)) cout << "INSIDE\n";
    else cout << "OUTSIDE\n";
}
*/

int N, M;

int main() {
    cin >> N >> M;

    vector<Point> v(N);
    for (int i = 0; i < N; i++)
        cin >> v[i].x >> v[i].y;

    cout << area(v) << endl;
    return 0;
}
