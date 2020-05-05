/*
 * Sink.cpp
 *
 *  Created on: May 4, 2020
 *      Author: Somya
 */

#include<string.h>
#include<omnetpp.h>
#include "Sink.h"

using namespace omnetpp;
using namespace std;

class Sink: public cSimpleModule {
    private:
        double x,y;
        int velocity;
        int nodeId;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;

        void drawPath();
};

Define_Module(Sink);

void Sink::initialize(){
    // initializing class variables
    x = par("x").doubleValue();
    y = par("y").doubleValue();
    velocity = par("velocity").intValue();

    //setting display position
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);

    //setting refresh rate for sink motion
    getSystemModule()->getCanvas()->setAnimationSpeed(0.5, this);
    drawPath();
}

void Sink::handleMessage(cMessage *msg){

}

void Sink::refreshDisplay() const {
    double time = simTime().dbl();
    pair<double,double> newCoord = getSinkLocation(1150, 600, 600, 600, 550, velocity, time);

    double x = newCoord.first;
    double y = newCoord.second;
//    par("x").setDoubleValue(x);
//    par("y").setDoubleValue(y);
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);
}

void Sink::drawPath() {
    cOvalFigure *ring = new cOvalFigure("sink path");
    ring->setOutlined(true);
    ring->setFilled(false);
    ring->setVisible(true);
    ring->setLineWidth(2);
    ring->setBounds(cFigure::Rectangle(600-520,600-520,1040,1040));
    cCanvas *canvas = getSystemModule()->getCanvas();
    canvas->addFigure(ring);
}
