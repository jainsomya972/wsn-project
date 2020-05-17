
#include <omnetpp.h>

using namespace omnetpp;
class DataMsg:public cMessage
{
   public:
            int senderId;
            int chId;
            int pkLength;
            int data;
            int clusterId;

        DataMsg(){
          senderId=-1;
          chId=-1;
          pkLength=3;
          data=0;
          clusterId=-1;
        }

        DataMsg(int sid,int  chid,int pklength,int d,int cid){
            senderId=sid;
              chId=chid;
              pkLength=pklength;
              data=d;
              clusterId=cid;
        }

        DataMsg(const DataMsg *msg){
            senderId = msg->senderId;
            chId = msg->chId;
            pkLength = msg->pkLength;
            data = msg->data;
            clusterId = msg->clusterId;
        }
};
