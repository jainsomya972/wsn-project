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
#include<vector>
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

        vector<cModule *> neighbours;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        void getNeighbours();
        void sendNeighbours(MsgOne *msg);
        bool isCenterOfCluster();
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
        par("x").setDoubleValue(x);
        par("y").setDoubleValue(y);
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
        MsgOne *msg1 = dynamic_cast<MsgOne *>(msg);
//        and str.compare("Init")==0
        if(msg->isSelfMessage() && str.compare("Init")==0){

         if(isCenterOfCluster()){

            //finding meighbours
             chId = getId();
            getNeighbours();
            string s = "C:"+to_string(clusterId)+" CH:"+to_string(chId)+" E:"+to_string(energy);
            bubble(s.c_str());
            getDisplayString().setTagArg("i", 0, "misc/node_s");
            sendNeighbours(new MsgOne(getId(),getId(),energy,0,clusterId));
         }
      }
      else if(msg1){
//          bubble("I got the message");
          if(clusterId == msg1->clusterId && chId != msg1->chId){

          }
      }
}


void Sensor::getNeighbours(){
    for(int i=0;i<noOfNodes;i++){
         cModule *node= getParentModule()->getSubmodule("n", i);
         int nx = node->par("x").doubleValue();
         int ny = node->par("y").doubleValue();
         if(distance(nx,ny,x,y) <= txRadius)
              neighbours.push_back(node);
    }
}

bool Sensor::isCenterOfCluster(){
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
     if(id == getId())
         return true;
     else
         return false;
}

void Sensor::sendNeighbours(MsgOne *msg){
    for(int i=0;i<neighbours.size();i++){
        sendDirect(new MsgOne(msg), neighbours[i],"in");
    }
}


