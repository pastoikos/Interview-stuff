import matplotlib.pyplot as plt

# -----------------------------
# 1) ΒΑΛΕ ΕΔΩ ΤΑ ΣΗΜΕΙΑ ΣΟΥ
# -----------------------------
points = [
     (2, 2), (1, 1), (2, 1),
    (1, 3), (2, 3), (3, 2), (1, 0), (2, 0), (0, 2), (3, 1),
    (1.5, 1.5), (0.5, 1), (2.5, 2.5), (2.2, 0.7), (0.2, 2.8)
]

# -----------------------------
# 2) GEOMETRY HELPERS
# -----------------------------
def cross(p, q, r):
    """
    cross(p,q,r) = (q - p) x (r - p)
    >0 : CCW (left turn)
    <0 : CW  (right turn)
    =0 : collinear
    """
    return (q[0] - p[0]) * (r[1] - p[1]) - (q[1] - p[1]) * (r[0] - p[0])

def dist2(a, b):
    dx, dy = a[0] - b[0], a[1] - b[1]
    return dx*dx + dy*dy

# -----------------------------
# 3) JARVIS MARCH (GIFT WRAPPING)
# -----------------------------
def jarvis_march(pts):
    n = len(pts)
    if n < 3:
        return pts[:]

    # start = leftmost (min x), tie by min y
    start = min(range(n), key=lambda i: (pts[i][0], pts[i][1]))

    hull = []
    p = start

    while True:
        hull.append(pts[p])

        # initial candidate q: any point != p
        q = (p + 1) % n
        if q == p:
            q = (p + 2) % n

        # find most CCW point relative to p
        for r in range(n):
            if r == p:
                continue

            s = cross(pts[p], pts[q], pts[r])

            # Want "more CCW": s > 0
            # If collinear: keep farthest (outermost)
            if s < 0 or (s == 0 and dist2(pts[p], pts[r]) > dist2(pts[p], pts[q])):
                q = r

        p = q
        if p == start:
            break

    return hull

# -----------------------------
# 4) PLOT + EDGE ORDER LABELS
# -----------------------------
def plot_points_and_hull(pts, hull):
    plt.figure(figsize=(7, 7))

    # plot all points
    xs, ys = zip(*pts)
    plt.scatter(xs, ys)

    # label points (P0, P1, ...)
    for i, (x, y) in enumerate(pts):
        plt.text(x + 0.05, y + 0.05, f"P{i}({x},{y})", fontsize=8)

    # plot hull edges in the order they are added: E0, E1, ...
    if len(hull) >= 2:
        for i in range(len(hull)):
            x1, y1 = hull[i]
            x2, y2 = hull[(i + 1) % len(hull)]

            plt.plot([x1, x2], [y1, y2], linewidth=2)

            # edge label at midpoint
            mx, my = (x1 + x2) / 2, (y1 + y2) / 2
            plt.text(mx, my, f"E{i}", fontsize=11)

    plt.title("All points + Convex Hull (Jarvis March) with Edge Order")
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)
    plt.show()

# -----------------------------
# 5) RUN
# -----------------------------
if __name__ == "__main__":
    hull = jarvis_march(points)

    print("Convex Hull vertices (order):")
    for i, p in enumerate(hull):
        print(f"V{i}: {p}")

    print("\nEdges in order:")
    for i in range(len(hull)):
        a = hull[i]
        b = hull[(i + 1) % len(hull)]
        print(f"E{i}: {a} -> {b}")

    plot_points_and_hull(points, hull)