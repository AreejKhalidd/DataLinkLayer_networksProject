//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __DATA_LINK_LAYER_PROTOCOLS_SIMULATION_NODE_H_
#define __DATA_LINK_LAYER_PROTOCOLS_SIMULATION_NODE_H_

#include <omnetpp.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    //std::fstream my_file;
    //std::fstream output;
    std::fstream dataFile;
    bool finished = false;
    bool ended = false;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    bool sender = false;
    vector<string> messages;
    vector <string> errors;
    bool ACK = false;
    bool NACK = false;
    bool dup_msg = false;
};

#endif
