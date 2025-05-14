package project;
simple Node {
    parameters:
        int nodeId;
        int numPeers;
        int gateSize;
        double blockGenInterval @unit(s) = exponential(2s);  // only for node 0
        @display("i=block/network2");
     	@signal[blockPropagationDelay];
    gates:
        input in[gateSize];
        output out[gateSize];
}
