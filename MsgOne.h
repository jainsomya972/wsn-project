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

      MsgOne(int sid,int  chid,int chenergy,int hopcount,int cid){
          senderId = sid;
          chId = chid;
          chEnergy = chenergy;
          hopCount = hopcount;
          clusterId = cid;
      }

      MsgOne(const MsgOne *msg){
          senderId = msg->senderId;
          chId = msg->chId;
          chEnergy = msg->chEnergy;
          hopCount = msg->hopCount;
          clusterId = msg->clusterId;
      }

};
