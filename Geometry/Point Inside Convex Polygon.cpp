
typedef vector<point> polygon;
struct convex_container {
    polygon pol;

    // Polygon MUST be in counter clockwise order
    convex_container(polygon p) : pol(p) {
        int pos = 0;

        for (int i = 1; i < SZ(p); ++i) {
            if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
                pos = i;
        }

        rotate(pol.begin(), pol.begin() + pos, pol.end());
    }

    bool contains(point p) {
        point c = pol[0];

        if (p.y < c.y || (pol.back() - c).cross(p - c) > 0)
            return false;

        int lo = 1, hi = SZ(pol) - 1;

        while (lo + 1 < hi) {
            int m = (lo + hi) / 2;
            if ((pol[m] - c).cross(p - c) >= 0)
                lo = m;
            else
                hi = m;
        }

        return (pol[lo + 1] - pol[lo]).cross(p - pol[lo]) >= 0;
    }
};
