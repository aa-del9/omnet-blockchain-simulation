#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    nodeId = par("nodeId");
    numPeers = par("numPeers");
    delaySignal = registerSignal("blockPropagationDelay");

    if (nodeId == 0) {
        // Creator node: generate the block
        BlockMessage *block = new BlockMessage("Block");
        block->setBlockId(1);
        block->setCreatedAt(simTime());
        scheduleAt(simTime() + par("blockGenInterval").doubleValue(), block);
    }
}

void Node::handleMessage(cMessage *msg)
{
    BlockMessage *block = check_and_cast<BlockMessage *>(msg);

    if (!hasReceivedBlock) {
        hasReceivedBlock = true;
        simtime_t delay = simTime() - block->getCreatedAt();
        emit(delaySignal, delay);

        EV << "Node " << nodeId << " received block "
           << block->getBlockId() << " after " << delay << "s\n";

        // Propagate to peers
        sendBlockToPeers(block->dup());
    }

    delete block;
}

void Node::sendBlockToPeers(BlockMessage *block)
{
    for (int i = 0; i < gateSize("out"); ++i) {
        // Only send if gate is connected
        if (gate("out", i)->isConnected() && uniform(0, 1) < 0.9) {
            send(block->dup(), "out", i);
        }
    }
    delete block;
}
