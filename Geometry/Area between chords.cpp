
/*
    Given 3 points in circumference,
    It returns the area between the chord AB and AC
*/
ld ang(const Point &P) const{ return abs(ang() - P.ang()); } // Uses Alaneos777
ld area_conic(Point<ld> A, Point<ld> B, Point<ld> C){

    ld A1 = abs((B-A).cross(C-A)) / 2;
    ld theta = (C-A).ang(B-A); 

    if(ge(theta, pi))
        theta = 2*pi - theta;

    ld sin_theta = 2*sinl(theta);

    ld r2 = (B-C).length2() / (sin_theta*sin_theta);
    ld ans = A1 + r2 * (theta - sinl(2*theta)/2);

    return ans;
}

