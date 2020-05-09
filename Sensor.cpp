/*
 * Sink.cpp
 *
 *  Created on: May 4, 2020
 *      Author: Somya
 */

#include<string.h>
#include<omnetpp.h>
#include<stdlib.h>
#include "position.h"

using namespace omnetpp;
using namespace std;

class Sensor: public cSimpleModule {
    private:
        double x,y,energy;
        int nodeId;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Sensor);

void Sensor::initialize(){
    // initializing parameters
    x = par("x").doubleValue();
    y = par("y").doubleValue();
//    x = atof(getDisplayString().getTagArg("p", 0));
//    y = atof(getDisplayString().getTagArg("p", 1));

    if(distance(x,y,600,600)>500){
        pair<int,int> res = getNodeCoordsInCircle(x, y, 600, 600, 500);
        x = res.first;
        y = res.second;
//        getDisplayString().setTagArg("p", 0, x);
//        getDisplayString().setTagArg("p", 1, y);
    }
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

//    scheduleAt(100.0, new cMessage("Hoax"));
}

void Sensor::handleMessage(cMessage *msg){

}
