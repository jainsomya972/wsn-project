#include<math.h>

using namespace std;

pair<double,double> getSinkLocation(int index, int sinks, double cx,double cy, double radius, double velocity, double time){
    double alpha = velocity*time/radius;
    double beta = (2*PI/sinks)*index;
    double theta = alpha + beta;
    double rx = radius*cos(theta)+cx;
    double ry = radius*sin(theta)+cy;
    return make_pair(rx,ry);
}

void getInitLocation(double &ix, double &iy, int cx, int cy, int r, int sinks, int index){
    double theta = (2*PI/sinks)*index;
    ix = cx+r*cos(theta);
    iy = cy+r*sin(theta);
}
