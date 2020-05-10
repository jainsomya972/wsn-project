/*
 * Sink.cpp
 *
 *  Created on: May 4, 2020
 *      Author: Somya
 */

#include<string.h>
#include<omnetpp.h>
#include<stdlib.h>
#include<iostream>
#include "position.h"
#include "MsgOne.h"
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
        simsignal_t broadcastSignalId;

        vector<cModule> neighbours;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void getNeighbours();
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
    energy=par("energy").doubleValue();
    //to check this
    if(distance(x,y,600,600)>500){
        pair<int,int> res = getNodeCoordsInCircle(x, y, 600, 600, 500);
        x = res.first;
        y = res.second;
    }
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

    broadcastSignalId = registerSignal("cHeadElectionMsg");

    clusterId = getClusterId(x,y,600,600,networkRadius, noOfClusters);
    par("clusterId").setIntValue(clusterId);

    scheduleAt(0.1,new cMessage("Init"));
}

void Sensor::handleMessage(cMessage *msg){

    //   cMessage *msg1 = new cMessage(msgOne);
        string str(msg->getName());
//        and str.compare("Init")==0
        if(msg->isSelfMessage()){
         int min=INT_MAX;int id;

         for(int i=0;i<noOfNodes;i++){
             cModule *node= getParentModule()->getSubmodule("n", i);
             int nx = node->par("x").doubleValue();
             int ny = node->par("y").doubleValue();

             pair<double,double> p = getClusterCenter(600, 600, noOfClusters, clusterId, networkRadius);
             if(distance(nx,ny,p.first,p.second)<min && clusterId == node->par("clusterId").intValue()){
                     min=distance(nx,ny,p.first,p.second);
                     id=node->getId();
             }
           }
         if(id==getId()){
             //start message transfer
                    //means its cluster head
                    MsgOne * msgOne=new MsgOne();
                    msgOne->chId=getId();
                    msgOne->chEnergy=energy;
                    msgOne->hopCount=0;
                    msgOne->senderId=getId();
                    msgOne->clusterId=clusterId;
                    //emit(20,&msgOne);
                    //emit(lengthSignalId, queue.length());
                    cout<<"initiated by : "<<getId()<<endl;
                    cModule *sink = getParentModule()->getSubmodule("n", 1);
                    sendDirect(msgOne, sink,"in");

         }
      }

}


