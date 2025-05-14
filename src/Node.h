#ifndef __BLOCKCHAINSIM_NODE_H
#define __BLOCKCHAINSIM_NODE_H

#include <omnetpp.h>
#include "BlockMessage_m.h"

using namespace omnetpp;

class Node : public cSimpleModule
{
  private:
    int nodeId;
    int numPeers;
    bool hasReceivedBlock = false;
    simsignal_t delaySignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendBlockToPeers(BlockMessage *block);
};

#endif
