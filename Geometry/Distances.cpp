// Complete with Alaneos777's reference

ld distancePointSegment(point a, point b, point p) {
    if ((b - a).dot(p - a) < 0)
        return (a - p).length();
    if ((a - b).dot(p - b) < 0)
        return (b - p).length();
    return distancePointLine(a, b - a, p);
}