package project;

network BlockchainNetwork {
    parameters:
        int numNodes = default(10);
    submodules:
        node[numNodes]: Node {
            parameters:
                nodeId = index;
                gateSize = parent.numNodes;
        }
    connections allowunconnected:
         for i=0..numNodes-1, for j=0..numNodes-1 {
            node[i].out++ --> { delay = uniform(10ms, 50ms); } --> node[j].in++
                if i!=j;
        }

}
