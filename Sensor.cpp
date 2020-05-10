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
        int networkRadius;
        int txRadius;
        int noOfClusters;
        int noOfNodes;
        int noOfSinks;

        int clusterId = -1;
        int chId = -1;
        int relayId = -1;
        int hopCount = -1;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Sensor);

void Sensor::initialize(){
    // initializing parameters
    x = par("x").doubleValue();
    y = par("y").doubleValue();
    nodeId = getId();
    cModule *network = getParentModule();
    networkRadius = network->par("networkRadius");
    txRadius = network->par("txRadius");
    noOfClusters = network->par("noOfClusters");
    noOfNodes = network->par("noOfNodes");
    noOfSinks = network->par("noOfSinks");


    if(distance(x,y,600,600)>500){
        pair<int,int> res = getNodeCoordsInCircle(x, y, 600, 600, 500);
        x = res.first;
        y = res.second;
    }
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

    clusterId = getClusterId(x,y,600,600,networkRadius, noOfClusters);
    par("clusterId").setIntValue(clusterId);

    scheduleAt(getId(), new cMessage("Hoax"));
}

void Sensor::handleMessage(cMessage *msg){
            cModule *sink = getParentModule()->getSubmodule("s", 0);
            sendDirect(new cMessage("Hello"), sink,"in");

}
