package data_link_layer_protocols_simulation;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=330,226");
    submodules:
        coordinator: Coordinator {
            @display("p=97,74");
        }
        node0: Node {
            @display("p=82,161");
        }
        node1: Node {
            @display("p=207,161");
        }
    connections:
        coordinator.out[0] --> node0.inCoordinator;
        coordinator.out[1] --> node1.inCoordinator;
        node0.out --> node1.in;
        node1.out --> node0.in;
}

