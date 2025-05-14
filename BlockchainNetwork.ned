package project;

network BlockchainNetwork {
    parameters:
        int numNodes = default(10);
    submodules:
        node[numNodes]: Node {
            parameters:
                nodeId = index;
        }
    connections allowunconnected:
        for i = 0 .. numNodes * numNodes - 1 {
            int src = i / numNodes;
            int dest = i % numNodes;
            if (src != dest) {
                node[src].out++ --> delay(uniform(10ms, 50ms)) --> node[dest].in++;
            }
        }
}
