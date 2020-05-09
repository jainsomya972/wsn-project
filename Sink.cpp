/*
 * Sink.cpp
 *
 *  Created on: May 4, 2020
 *      Author: Somya
 */

#include<string.h>
#include<omnetpp.h>
#include<iostream>
#include<math.h>
#include "Sink.h"

using namespace omnetpp;
using namespace std;

class Sink: public cSimpleModule {
    private:
        double x,y;
        double cx = 600,cy = 600; // center of canvas
        int velocity;
        int id;
        int index;

        int noOfSinks;
        int noOfClusters;
        int networkRadius;

        cCanvas *canvas;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;

        void drawPath();
        void drawClusters();
};

Define_Module(Sink);

void Sink::initialize(){
    // initializing sink variables
    velocity = par("velocity").intValue();
    id = getId();
    index = getIndex();

    noOfSinks = getAncestorPar("noOfSinks").intValue();
    noOfClusters = getAncestorPar("noOfClusters").intValue();
    networkRadius = getAncestorPar("networkRadius").intValue();

    getInitLocation(x, y, 600, 600, networkRadius + 50, noOfSinks, index);

    //setting display position
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

    //setting refresh rate for sink motion
    canvas = getSystemModule()->getCanvas();
    canvas->setAnimationSpeed(0.5, this);
    drawPath();
    drawClusters();

    scheduleAt(0.5, new cMessage("refresh display"));
}

void Sink::handleMessage(cMessage *msg){

    if(msg->isSelfMessage()){
        double time = simTime().dbl();
        pair<double,double> newCoord = getSinkLocation(index, noOfSinks, cx, cy, networkRadius + 50, velocity, time);

        x = newCoord.first;
        y = newCoord.second;
        par("x").setDoubleValue(x);
        par("y").setDoubleValue(y);
        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);

        scheduleAt(simTime()+0.5,msg);
    }
}

void Sink::refreshDisplay() const {
}

void Sink::drawPath() {
    cOvalFigure *ring = new cOvalFigure("sink path");
    int r = networkRadius;
    ring->setOutlined(true);
    ring->setFilled(false);
    ring->setVisible(true);
    ring->setLineWidth(2);
    ring->setBounds(cFigure::Rectangle(cx-r-20,cy-r-20,2*r + 40,2*r + 40));
    canvas->addFigure(ring);
}

void Sink::drawClusters(){
    cLineFigure *line;
    int r = networkRadius;
    for(int i=0;i<noOfClusters;i++){
        double theta = (2*PI/noOfClusters)*i;

        line = new cLineFigure("cluster boundary");
        line->setStart(cFigure::Point(cx,cy));
        line->setEnd(cFigure::Point(cx + r*cos(theta), cy + r*sin(theta)));
        line->setLineWidth(2);
        canvas->addFigure(line);
    }
}
