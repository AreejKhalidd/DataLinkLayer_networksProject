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
#include <iostream>
#include <ostream>
using namespace std;
Define_Module(Node);
// dup by 0.01
// delay by 0.01
//send msg in same frame by 0.05
//time out 0.1
// delete msg ???????????
void Node::initialize()
{
    // TODO - Generated method body
//    ofstream f;
//    f.open ("../outputs/pair01.txt",std::ios_base::app);
//    f.close();
    std::ofstream ofs;
    ofs.open("../outputs/pair01.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
void Node::intializeLogFile(string nodeName)
{
    if (nodeName == "node0" ||nodeName == "node1" )
    {
        logFile = "pair01.txt";
    }
    if (nodeName == "node2" ||nodeName == "node3" )
    {
        logFile = "pair23.txt";
    }
    if (nodeName == "node4" ||nodeName == "node5" )
    {
        logFile = "pair45.txt";
    }
    ofstream f;
    f.open ("../outputs/"+logFile,std::ios_base::app);
    f.close();
}
void Node::addtoLogFile(string msg)
{
    ofstream f;
    f.open ("../outputs/"+logFile,std::ios_base::app);
    f << msg+"\n";
    f.close();
}
void Node::receiverStart(MyMessage_Base * mmsg)
{
    const char* str=getName();
    std::string s = str;
    intializeLogFile(s);
    string m4 = s + " : received msg from coordinator...";
    EV << m4 << endl;
    addtoLogFile(m4);
    sender = false;

    EV <<"Receiver start reading from file.." << endl;
                    string m3 = s + " : Receiver to reading data from file";
                    EV << m3 <<endl;
                    addtoLogFile(m3);
                    string file_name = "../inputsSamples/";
                    cout << "File name from msg: " << mmsg->getM_Payload() <<endl;
                    file_name = file_name + mmsg->getM_Payload();
                    cout << "File name: " << file_name <<endl;
                    //read file
                    dataFile.open(file_name, std::ios::in);
                    if (!dataFile)
                        ended = true;
                    else
                        ended = false;
                     string line;
                     // read all meassages
                     int max = 0;
                     while (getline(dataFile, line))
                     {
                         max ++;
                         cout << "Node start read new line" <<endl;
                         vector<string> inputs_arr;
                         string error_input = line.substr(0,4);
                         errors.push_back(error_input);
                         cout << "error is : " << error_input <<endl;
                         string msg_input = line.substr(5,std::string::npos);
                         cout << " msg is : " << msg_input <<endl;
                         messages.push_back(msg_input);
                     }
                     // LOG FILE

                     const char* str1=getName();
                     std::string s1 = str1;
                     string ww = s1 + " : finished reading from file...";
                     EV << ww << endl;
                     addtoLogFile(ww);
                     cout << "Receiver node finish reading from file" <<endl;
                     windowSize = (max ) / 2;
                     string op = "number of msgs = " + to_string(max) + " and window size = " + to_string(windowSize)+"..";
                     addtoLogFile(op);
                     // Self message with start time
//                     MyMessage_Base * msg_s = new MyMessage_Base();
//                     msg_s->setSeq_Num(start);
//                     msg_s->setM_Type(type);
//                     msg_s->setM_Payload("Receiver sending..");
//                     string Payload=msg_s->getM_Payload();
//                              string binaryStr="";
//                                              for (int i = 0; i < Payload.length(); i++)
//                                              {
//                                                      bitset<8> binaryBits(Payload[i]);
//                                                      binaryStr+=binaryBits.to_string();
//                                              }
//                                              cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
//                              string CRCStr=calculateCRC(binaryStr);
//
//                     cout<<"CRC Bits: "<<CRCStr<<endl;
//                     EV<<"CRC Bits: "<<CRCStr<<endl;
//                     bits CRCbits(CRCStr);
//                     msg_s->setMycheckbits(CRCbits);
//                     EV <<"Receiver schedule self message" << endl;
                     //scheduleAt(start, msg_s);
}
void Node::senderStart(int start,MyMessage_Base * mmsg)
{
    const char* str=getName();
                std::string s = str;
                sender = true;
                intializeLogFile(s);
                string h = s + " : received msg from coordinator";
                addtoLogFile(h);
                // LOG FILE
                EV <<"Sender start reading from file.." << endl;
                string m3 = s + " : start to reading data from file";
                EV << m3 <<endl;
                addtoLogFile(m3);
                string file_name = "../inputsSamples/";
                cout << "File name from msg: " << mmsg->getM_Payload() <<endl;
                file_name = file_name + mmsg->getM_Payload();
                cout << "File name: " << file_name <<endl;
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
                 // LOG FILE
                 windowSize = ( messages.size() ) /2;
                 const char* str1=getName();
                 std::string s1 = str1;
                 string m4 = s1 + " : finished reading from file...";
                 EV << m4 << endl;
                 addtoLogFile(m4);
                 m4 = "number of msgs = " + to_string(messages.size()) + " and window size = " + to_string(windowSize) + "..";
                 addtoLogFile(m4);
                 cout << "Sender node finish reading from file" <<endl;
                 // Self message with start time
                 MyMessage_Base * msg_s = new MyMessage_Base();
                 msg_s->setSeq_Num(start);
                 msg_s->setM_Type(6);
                 string Payload=msg_s->getM_Payload();
                          string binaryStr="";
                                          for (int i = 0; i < Payload.length(); i++)
                                          {
                                                  bitset<8> binaryBits(Payload[i]);
                                                  binaryStr+=binaryBits.to_string();
                                          }
                                          cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                          string CRCStr=calculateCRC(binaryStr);

                 cout<<"CRC Bits: "<<CRCStr<<endl;
                 EV<<"CRC Bits: "<<CRCStr<<endl;
                 bits CRCbits(CRCStr);
                 msg_s->setMycheckbits(CRCbits);
                 EV <<"Sender schedule self message" << endl;
                 scheduleAt(start, msg_s);
                 start_time = start;

}
int Node::nodeSendData(MyMessage_Base *mmsg)
{
    double reply=0;
    if(mmsg->getM_Type()!=4 && mmsg->getM_Type()!=6)
        reply=0.05;
    MyMessage_Base * msgg = new MyMessage_Base(); // new msg to be sent
    int acktype = mmsg->getackORnack();
    msgg->setpiggybackingID(msg_ack); // el ana 3yzahaaaaa tegy -> hazbtha fl receive
    double t = simTime().dbl();
    const char* str=getName();
    std::string s = str;
    double delayy=par("delay").doubleValue();
    // check if done sending msgs
    if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
    {
        // LOG FILE
        if (doneOnce == false)
        {
            cout << "Sender finish sending messages.." <<endl;
            string s0= s +  " : finish sending frames at time = " + to_string(t);
            EV << s0 <<endl;
            addtoLogFile(s0);
            doneOnce = true;
        }
        if(mmsg->getM_Type()==55)
        {
         //both finished
            msgg->setM_Type(55);
            cout << "Both nodes finished..session finished.." <<endl;
            string s0= "Both nodes finished..session finished.. at time = " + to_string(t);
            EV << s0 <<endl;
            addtoLogFile(s0);
            return 1;
        }
            msgg->setM_Type(55);
            sendDelayed(msgg,reply,"out");//send(msgg,"out");
            return 1;

    }
    //start sending new frame
    //if(getM_type()==2)
    int index_msg = msg_seqno;
    msgg->setM_Type(1);
    msgg->setSeq_Num(index_msg);
    string error_msg = "";
    string error_msg_type = "";
    //byte stuffing
    msgg->setM_Payload(byteStuffing(messages[index_msg]).c_str());
    //here we set to the msg the check bits(CRC)
    //getCRCtoSend(msgg);
    //converting message to binary string
    string Payload=msgg->getM_Payload();
    string binaryStr="";
                    for (int i = 0; i < Payload.length(); i++)
                    {
                            bitset<8> binaryBits(Payload[i]);
                            binaryStr+=binaryBits.to_string();
                    }
                    cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
    string CRCStr=calculateCRC(binaryStr);
    cout<<"CRC Bits: "<<CRCStr<<endl;
    EV<<"CRC Bits: "<<CRCStr<<endl;
    bits CRCbits(CRCStr);
    msgg->setMycheckbits(CRCbits);
    // Errors
    string curr_error = errors[index_msg];
    int out = -1;
    // curr_error = 1101
    char mod_error = curr_error[0];
    char loss_error = curr_error[1];//out = 0 -> loss
    char dup_error = curr_error[2];// out = 2 -> dup
    char delay_error = curr_error[3];// out = 1 -> delayed
    bool loss = false;/// out = 3 -> dup w delay
     if(loss_error == '1') //skip this message
     {
         loss =  true;
         double t = simTime().dbl();
         const char* str=getName();
         std::string s = str;
         error_msg = s + " : will drop message with id = " +  to_string(msg_seqno) +
                 " and content = " +  msgg->getM_Payload() +
                   "and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " +  to_string(t);
         cout << "loss msg" <<endl;
         addtoLogFile(error_msg);
         out = 0;
         msg_seqno++;
         //schedule new event to complete (Self message )
         msgg->setM_Type(4);
         scheduleAt(simTime()+0.1, msgg);
         num_transmissions++;
     }

     if(mod_error == '1' && loss == false)
     {
          cout << "modi msg " << endl;
          error_msg_type = error_msg_type + " Modification ";
          int index=uniform(0,1)*10;
          const char* str = msgg->getM_Payload();
          string s = str;
          int size = s.size();
          while (index > size-1)
          {
              index=uniform(0,1)*10;
          }
          string mypayload= msgg->getM_Payload();
          mypayload[index]=mypayload[index]+2;
          msgg->setM_Payload(mypayload.c_str());
          cout << "msg after modi " << msgg->getM_Payload() <<endl;
     }
     if(dup_error == '1'&& loss == false)
     {
         cout << "dup msg " << endl;
         error_msg_type = error_msg_type + " with Duplication ";
         MyMessage_Base * msg_s = new MyMessage_Base();
         msg_s->setSeq_Num(msgg->getSeq_Num());
         msg_s->setM_Type(1);
         msg_s->setM_Payload( msgg->getM_Payload());
         msg_s->setpiggybackingID( msgg->getpiggybackingID());
         msg_s->setMycheckbits(msgg->getMycheckbits());
        EV << " AHUU H3ML SCHEDULE to send dupp att "  << simTime() + 0.01  << endl;
        num_transmissions++;
         double time = reply+0.01;
         if (out == 1 )
         {
              time = time + delayy;
              out = 1;
         }
         else{
             out = 2;
         }
              sendDelayed(msg_s,time,"out");
              num_transmissions++;
     }
     if(delay_error == '1' && loss == false)
     {
           cout << "delayed msg " << endl;
           error_msg_type = error_msg_type + " with delay ";
           double t = simTime().dbl();
           //addtoLogFile(error_msg);
           MyMessage_Base * msg_s = new MyMessage_Base();
           msg_s->setSeq_Num(msgg->getSeq_Num());
           msg_s->setM_Type(msgg->getM_Type());
           msg_s->setM_Payload( msgg->getM_Payload());
           msg_s->setpiggybackingID( msgg->getpiggybackingID());
           msg_s->setMycheckbits(msgg->getMycheckbits());
           double t2 = simTime().dbl();
           const char* str=getName();
           std::string s = str;
           error_msg = s + " : will send msg with id = "+  to_string(msg_seqno) +
                   " and content = " +msgg->getM_Payload()  +error_msg_type +
                   "and piggy backing ACK = "+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t) ;
           addtoLogFile(error_msg);
           sendDelayed(msg_s,reply+delayy,"out"); // delay in second from ini file
           msg_seqno++;
           num_transmissions++;
           out = 1;
     }
     if (out != 0 && out != 1) // not loss msg and not delayed msg
     {
         double t = simTime().dbl();
         const char* str=getName();
         std::string s = str;
         error_msg = s + " : will send msg with id = "+  to_string(msg_seqno) +
                 " and content = " +msgg->getM_Payload()  +error_msg_type +
                 "and piggy backing ACK = "+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t) ;
         addtoLogFile(error_msg);
         sendDelayed(msgg,reply,"out");//send(msgg,"out"); // dup w delay m3 b3d???
         num_transmissions++;
         msg_seqno++;
     }
     // done send msg
     EV << error_msg ; //LOG FILE
return 1;
}
int Node:: nodeReceiveData(MyMessage_Base *mmsg) // lma ba-recieve bazbt msg_Ack el ana 3yzah
{
    if(mmsg->getM_Type() == 55)
    {
        MyMessage_Base * msg1 = new MyMessage_Base(" ");
        msg1->setM_Type(55);
        msg1->setpiggybackingID(mmsg->getpiggybackingID());
        double t = simTime().dbl();
        const char* str=getName();
        std::string s = str;
        string error_msg = s + " : received nothing as the paired node finished"
                + " at time = " + to_string(t);
        addtoLogFile(error_msg);
        nodeSendData(msg1);
        return 1;
        if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
            {
                // LOG FILE
                if (doneOnce == false)
                {
                    cout << "Sender finish sending messages.." <<endl;
                    string s0= s +  " : finish sending frames at time = " + to_string(t);
                    EV << s0 <<endl;
                    addtoLogFile(s0);
                    doneOnce = true;
                }
                if(mmsg->getM_Type()==55)
                {
                 //both finished
                    msg1->setM_Type(55);
                    cout << "Both nodes finished..session finished.." <<endl;
                    string s0= "Both nodes finished..session finished.. at time = " + to_string(t);
                    EV << s0 <<endl;
                    addtoLogFile(s0);
                    return 1;
                }
                    msg1->setM_Type(55);
                    send(msg1,"out");
                    return 1;

            }

    }

    string mymsg = mmsg->getM_Payload();
    // error detection by crc
    string characterCRC = (mmsg->getMycheckbits()).to_string();
    string Payload=mmsg->getM_Payload();
    string binaryStr="";
    for (int i = 0; i < Payload.length(); i++)
    {
             bitset<8> binaryBits(Payload[i]);
             binaryStr+=binaryBits.to_string();
    }
    cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
    binaryStr=binaryStr+characterCRC[5]+characterCRC[6]+characterCRC[7];
    string CRCStr=calculateCRC(binaryStr);
    cout<<"CRC Bits: "<<CRCStr<<"   "<<binaryStr <<"     "<<binaryStr.length()<<endl;
    EV<<"CRC Bits: "<<CRCStr<<endl;
    bits CRCbits(CRCStr);
    string errordetection = "";
    bits zeross(0);
    int err_typee;
    if(CRCbits==zeross)
    {
        err_typee=2;// ACK no error
        errordetection = errordetection + "ACK = 2 ";
    }
    else
    {
        err_typee=3;// NACK error
        errordetection = errordetection + "  with Modification and NACK = 3";
    }
    // de-stuffing
    string final_msg = deStuffing(mymsg);
    string error_msg = "";
    // Detect frame to deceide ack or nack
    if(mmsg->getSeq_Num() < msg_ack )
        {
            double t = simTime().dbl();
            const char* str=getName();
            std::string s = str;
            error_msg = s + " : received and drop  duplicated message with id = " +to_string(mmsg->getSeq_Num())+"With NACK = 5" +" with content = "+ final_msg
                    +"and piggy backing ACK ="+  to_string(msg_ack)
                    + " at time = " + to_string(t);
            cout << "Receiver Dup frame .. discard frame " <<endl;
            // LOG FILE
            EV << error_msg <<endl;
            addtoLogFile(error_msg);
            // msh hn3ml haga hya kdakda duplicated message
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(1);
            msg1->setpiggybackingID(mmsg->getpiggybackingID());
            msg1->setackORnack(5);
            nodeSendData(msg1);//sendACK(msg1);//sendDelayed(msg1,0.2,"out");
        }
    else if (mmsg->getSeq_Num() > msg_ack)
    {
        double t = simTime().dbl();
        cout << "Receiver ..received frame( loss message occured) .. send new ACK" << endl;
        const char* str=getName();
        std::string s = str;
        error_msg = s + " : received message (messaged lost before this message ) with id = " +  to_string(mmsg->getSeq_Num()) +
                " and content = " +final_msg   + errordetection +
                  "and piggy backing ACK ="+  to_string(msg_ack) +" at time = "  + to_string(t);
        msg_ack = mmsg->getSeq_Num();
        // LOG FILE
        EV << error_msg <<endl;
        addtoLogFile(error_msg);
        msg_ack++;
        msg_ack++;
        MyMessage_Base * msg1 = new MyMessage_Base(" ");
        msg1->setM_Type(1);
        msg1->setackORnack(7);
        msg1->setpiggybackingID(mmsg->getpiggybackingID());
        nodeSendData(msg1);//sendACK(msg1);//sendDelayed(msg1,0.2,"out");
    }
    else
    {
        const char* str=getName();
        std::string s = str;
        double t = simTime().dbl();
        cout << "Receiver ..received frame .. send new ACK" << endl;
        error_msg = s + " : received message with id = " +  to_string(mmsg->getSeq_Num()) +
                " and content = " + final_msg + errordetection +
                  "  and piggy backing ACK ="+  to_string(msg_ack) +" at time = " + to_string(t) ;
        // LOG FILE
        EV << error_msg <<endl;
        addtoLogFile(error_msg);
        msg_ack++;
        MyMessage_Base * msg1 = new MyMessage_Base(" ");
        msg1->setM_Type(1);
        msg1->setpiggybackingID(mmsg->getpiggybackingID());
        msg1->setackORnack(err_typee);
        nodeSendData(msg1);//sendACK(msg1);// sendDelayed(msg1,0.2,"out");
}

return 1;
}
int Node::srSend(MyMessage_Base *mmsg)
{

//    while (msg_seqno<windowSize)
//    {
//
//    }
    return 1;
}
string Node:: byteStuffing (string msg_input)
{
     string final_payload = "$" ; // first flag byte
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
     cout << "Node will send message after byte stuffing : " << final_payload <<endl;
     return final_payload;
}

string Node:: deStuffing(string mymsg)
{
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
    return final_msg;
}
string XORString(string a, string b)
{
    string str="";
    for(int i=0;i<a.length();i++)
    {
        if(a[i]==b[i])
            str+="0";
        else
            str+="1";
    }
    return str;
}
/*
Main Concept of shifting bits and algorithm of CRC is got from : http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
*/
string Node::calculateCRC(string binaryStr)
{

                int j=0;
                string dividend="";
                string str="";
                bool first=true;
                while( j<(binaryStr.length()))
                {
                    //Ensure that MSB is 1
                    while(binaryStr[j]=='0' && str=="" && first)
                    {
                        j++;
                        first=false;
                    }
                       // >0?str.length()-1:0;
                    for(int z=(str.length());z<generator.length()&& j<binaryStr.length();z++)
                    {
                        str+=binaryStr[j];
                        j++;
                    }
                  //cout<<"jjjjjj"<<j<<"   "<<str<<endl;
                    if(str.length()<4)
                        break;
                    dividend=XORString(str,generator);
                    //cout<<dividend<<endl;
                    //int num=
                    str="";
                    str=stoi(dividend)>0?to_string(stoi(dividend)):"";
                     //cout<<j<<endl;

                }
                //cout<<j<<endl;
               // while(j<binaryStr.length())
                 //   str+=binaryStr[j++];
                if(str=="")
                    str="0";

                return str;
}

void Node::handleMessage(cMessage *msg)
{
    double delayy=par("delay").doubleValue();
    // TODO - Generated method body
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    int start = mmsg->getSeq_Num();
    int type = mmsg->getM_Type();
    if(msg->isSelfMessage()) // self message to start send messages to receiver node
    {
        double t = simTime().dbl();
        const char* str=getName();
        std::string s = str;
        //LOG FILE
        if (type == 6)
        {
            string m =  s +" : received self message to start sending messages at time = " + to_string(t) ;
            EV << m <<endl;
            addtoLogFile(m);
            int done = nodeSendData(mmsg);
        }

         if( type == 4 )
         {
             string m2 = s + " : time out .. complete sending messages";
             EV << m2 <<endl;
             addtoLogFile(m2);
             int done = nodeSendData(mmsg);
         }


    }
    else if( type == 0  ) // message from coordinator to any node (Sender/receiver)
    {
        if(start != -1 ) // if node is sender then read file
        {
            //sender
            senderStart(start,mmsg);
        }
        else // msg from coordinator to receiver
        {
            //receiver
            receiverStart(mmsg);
        }

    }
    else if( type == 1 || type == 2 || type == 3 || type == 5 ||  type == 55  || type == 7 )// receiver receive data message from the other node
    {
        int y = nodeReceiveData(mmsg); // receive data and send ACK (and send msg????)
        // 2 ACK
        // 3 NACK error in msg only
        // 3 in order,dup
        // 5 inorder,loss
    }

}
