#include<math.h>

using namespace std;

pair<double,double> getSinkLocation(double ix,double iy,double cx,double cy, double radius, double velocity, double time){
    double alpha = velocity*time/radius;
    double beta = atan((iy-cy)/(ix-cx));
    double theta = alpha + beta;
    double rx = radius*cos(theta)+cx;
    double ry = radius*sin(theta)+cy;
    return make_pair(rx,ry);
}
