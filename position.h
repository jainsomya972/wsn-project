#include<math.h>
#include<cstdlib>

using namespace std;

pair<int,int> getNodeCoordsInCircle(double x,double y, double cx, double cy, double radius){
    double rx,ry;
    double m = (y-cy)/(x-cx);
    double theta = atan(m);
    double yrange = radius*sin(theta);
    double xrange = radius*cos(theta);
    if(yrange > 0)
        ry = cy + rand()%abs(int(yrange));
    else
        ry = cy - rand()%abs(int(yrange));

    if(xrange > 0)
        rx = cx + rand()%abs(int(xrange));
    else
        rx = cx - rand()%abs(int(xrange));
    return make_pair(rx,ry);
}

double distance(double x1,double y1,double x2,double y2){
    return sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
}

int getClusterId(double x, double y, int cx, int cy, int radius, int clusters){
    double m = (y-cy)/(x-cx);
    double theta = atan(m);
    if(x<cx)
        theta+=PI;
    else if(x>cx && y<cy)
        theta+=2*PI;
    double block = 2*PI/clusters;
    return (theta/block + 1);
}
