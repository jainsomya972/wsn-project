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
#include "energy.h"
using namespace omnetpp;
using namespace std;

class Sensor: public cSimpleModule {
    private:
        double x,y,energy;

        int nodeId;
        int networkRadius;
        double txRadius;
        double epsFs,epsMp,eElec;
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

        //setters
        void setChId(int chid);
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
    epsFs =  network->par("epsFs").doubleValue();
    epsMp =  network->par("epsMp").doubleValue();
    eElec =  network->par("eElec").doubleValue();

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

    getNeighbours();
    scheduleAt(0.01*getId(),new cMessage("Init"));
}

void Sensor::handleMessage(cMessage *msg){

    //   cMessage *msg1 = new cMessage(msgOne);
        string str(msg->getName());
        MsgOne *msg1 = dynamic_cast<MsgOne *>(msg);
//        and str.compare("Init")==0
        if(msg->isSelfMessage() && str.compare("Init")==0){

         if(isCenterOfCluster()){

            //finding meighbours
            setChId(getId());
            string s = "C:"+to_string(clusterId)+" CH:"+to_string(chId)+" E:"+to_string(energy);
            bubble(s.c_str());
            getDisplayString().setTagArg("i", 0, "misc/node_s");
            sendNeighbours(new MsgOne(getId(),getId(),energy,0,clusterId));
         }
      }
      else if(msg1){

          energy -= RxEnergy(sizeof(MsgOne), eElec);
          par("energy").setDoubleValue(energy);

          //same cluster and different cluster head
          if(clusterId == msg1->clusterId && chId != msg1->chId){

              // our energy is less or (our energy is same but id is greater)
//              if(energy <= msg1->chEnergy){
                  cout<<"CH recieved!\n";
                  // accept the new CH and relay the msg
                  setChId(msg1->chId);
                  relayId = msg1->senderId;
                  hopCount = msg1->hopCount;

                  getDisplayString().setTagArg("i", 0, "misc/node2_vs");
                  sendNeighbours(new MsgOne(getId(),chId,msg1->chEnergy,hopCount+1,clusterId));
//              }
              // our energy is more or (energy is same and id is less)
//              else if(energy > msg1->chEnergy /*|| (energy == msg1->chEnergy && getId() < msg1->chId)*/ ){
//                  // announce self as new CH
//                  setChId(getId());
//                  relayId = -1;
//                  hopCount = 0;
//
////                  scheduleAt(simTime()+1,new cMessage("declare CH"));
//                  getDisplayString().setTagArg("i", 0, "misc/node_s");
//                  sendNeighbours(new MsgOne(getId(), getId(), energy, 0, clusterId));
//
//              }
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
    energy -= TxEnergy(sizeof(MsgOne)*8, txRadius, eElec, epsFs, epsMp);
    par("energy").setDoubleValue(energy);
}

void Sensor::setChId(int chid){
    chId = chid;
    par("chId").setIntValue(chId);
}


