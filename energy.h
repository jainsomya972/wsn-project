
#include<math.h>

using namespace std;

double TxEnergy(double l,double d,double eElec, double epsFs,double epsMp){
    double d0 = sqrt(epsFs/epsMp);
    if(d<d0){
        return (l*eElec+l*epsFs*d*d);
    }
    else{
        return (l*eElec + l*epsMp*pow(d,4));
    }
}

double RxEnergy(double l,double eElec){
    return l*eElec;
}
