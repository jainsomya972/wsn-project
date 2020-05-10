#include <omnetpp.h>

using namespace omnetpp;
class MsgOne:public cMessage{
    public:
        int senderId;
        int chId;
        int chEnergy;
        int hopCount;
        int clusterId;

      MsgOne(){
        senderId=-1;
        hopCount=0;

    }

};
