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

#include "node.h"
#include "MyMessage_m.h"
#include <stdlib.h> /* atoi */
using namespace std;
Define_Module(Node);
// delete msg ???????????
void Node::initialize()
{
    // TODO - Generated method body
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    int start = mmsg->getSeq_Num();
    int type = mmsg->getM_Type();
    if( type == 0  ) // message from coordinator
    {
        if(start != -1 ) // if node is sender then read file
        {
            sender = true;
            cout << "Node start to read data from file" <<endl;
            string file_name = "../inputsSamples/";
            cout << "File name from msg " << mmsg->getM_Payload() <<endl;
            file_name = file_name + mmsg->getM_Payload();
            cout << "File name " << file_name <<endl;
            //read file
            dataFile.open(file_name, std::ios::in);
            if (!dataFile)
                ended = true;
            else
                ended = false;
             string line;
             // read all meassages
             while (getline(dataFile, line))
             {
                 cout << "Node start read new line" <<endl;
                 vector<string> inputs_arr;
                 string error_input = line.substr(0,4);
                 errors.push_back(error_input);
                 cout << "error is : " << error_input <<endl;
                 string msg_input = line.substr(5,std::string::npos);
                 cout << " msg is : " << msg_input <<endl;
                 messages.push_back(msg_input);
             }

             for(int i =0;i<messages.size();i++ )
             {
                 MyMessage_Base * msgg = new MyMessage_Base(" ");
                 msgg->setM_Type(1);
                 msgg->setSeq_Num(0);
                 //check errors?


                 //byte stuffing
                 string final_payload = "$" ; // first flag byte
                 string msg_input = messages[i];
                 int msg_size = msg_input.size();
                 for(int i = 0;i<msg_size;i++)
                 {
                     if(msg_input[i] == '$' || msg_input[i] == '/') // if in msg esc or flag
                     {
                         final_payload = final_payload + '/' + msg_input[i] ; // add esc before it
                     }
                     else
                         final_payload = final_payload +  msg_input[i] ;
                 }
                 final_payload = final_payload + '$'; // last flag byte
                 msgg->setM_Payload(final_payload.c_str()); // check erros
                 cout << "Node send message before byte stuffing: " << msg_input <<endl;
                 cout << "Node send message after byte stuffing : " << final_payload <<endl;
                 send(msgg,"out");
             }

        }
        else
        {
            //receiver
            sender = false;
        }

    }
    else if( type == 1  )
    {
        // receiver receive message from node
        string mymsg = mmsg->getM_Payload();
        // de-stuffing
        string final_msg = "";
        for (int i = 1;i<mymsg.size();i++)
            {
               if(mymsg[i] == '/')
               {
                   final_msg = final_msg + mymsg[i+1];
                   i=i+1;
               }
               else if (mymsg[i] == '$')
                   break;
               else
                   final_msg = final_msg + mymsg[i];
            }
        cout << " Node received message and will send ACK or NACK"<<endl;
        cout << " message before de-stuffing "<< mymsg <<endl;
        cout << " message after de-stuffing "<< final_msg <<endl;
        // Detect errors
         MyMessage_Base * msg1 = new MyMessage_Base(" ");
         msg1->setM_Type(2);// send ACK
         msg1->setSeq_Num(0);
         send(msg1,"out");


    }
    else if (type == 2 || type == 3)
    {
        // ACK or NACK from receiver
    }


}
