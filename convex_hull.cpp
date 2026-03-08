// Jarvis March (Gift Wrapping) - Convex Hull in C++
// Convention used here:
// cross(p,q,r) = (q-p) x (r-p)
//  > 0 : counterclockwise (left turn)
//  < 0 : clockwise (right turn)
//  = 0 : collinear
//
// Handles collinear points by keeping the farthest one on the hull edge.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    long long x, y;
};

static long long cross(const Point& p, const Point& q, const Point& r) {
    // (q - p) x (r - p)
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

static long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

vector<Point> jarvisMarch(const vector<Point>& pts) {
    int n = (int)pts.size();
    if (n < 3) return pts;

    // Start = leftmost (min x). If tie, choose lowest y.
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (pts[i].x < pts[start].x ||
            (pts[i].x == pts[start].x && pts[i].y < pts[start].y)) {
            start = i;
        }
    }

    vector<Point> hull;
    int p = start;

    do {
        hull.push_back(pts[p]);

        // Pick an initial candidate q (any point different from p)
        int q = (p + 1) % n;
        if (q == p) q = (p + 2) % n;

        // Find the most counterclockwise point relative to p
        for (int r = 0; r < n; r++) {
            if (r == p) continue;

            long long s = cross(pts[p], pts[q], pts[r]);

            // If r is more CCW than current q, update q
            if (s < 0) {
                q = r;
            }
            // If collinear, keep the farthest point
            else if (s == 0 && dist2(pts[p], pts[r]) > dist2(pts[p], pts[q])) {
                q = r;
            }
        }

        p = q;
    } while (p != start);

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};

    vector<Point> hull = jarvisMarch(points);

    cout << "Convex Hull points (in order):\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
    return 0;
}