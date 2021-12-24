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

// delete msg ???????????
// (time delay) (random selected bit for modification )check hwar el random number lw h3mel add seedset fl ini

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
}
void Node::addtoLogFile(string msg){
    ofstream f;
    f.open ("../outputs/"+logFile,std::ios_base::app);
    f << msg+"\n";
    f.close();
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
//int Node:: checkErrorsType(string curr_error,MyMessage_Base * msgg)
//{
//    int out = -1;
//    //out = 0 -> loss
//    // out = 1 -> delayed
//    // out = 2 -> dup
//    /// out = 3 -> dup w delay
//    cout << "ERROR IS :" << curr_error <<endl;
//    // curr_error = 1101
//    char mod_error = curr_error[0];
//    char loss_error = curr_error[1];
//    char dup_error = curr_error[2];
//    char delay_error = curr_error[3];
//     if(loss_error == '1') //skip this message
//     {
//         out = 0;
//     }
//     if(mod_error == '1')
//     {
//          cout << "modi msg " << endl;
//          int index=uniform(0,1)*10;
//          const char* str = msgg->getM_Payload();
//          string s = str;
//          int size = s.size();
//          while (index > size-1)
//          {
//              index=uniform(0,1)*10;
//          }
//          string mypayload= msgg->getM_Payload();
//          mypayload[index]=mypayload[index]+5;
//          msgg->setM_Payload(mypayload.c_str());
//          cout << "msg after modi " << msgg->getM_Payload() <<endl;
//     }
//     if(delay_error == '1')
//     {
//         cout << "delayed msg " << endl;
//         sendDelayed(msgg,0.2,"out"); // delay in second from ini file
//         msg_seqno++;
//         out = 1;
//     }
//     if(dup_error == '1')
//     {
//         cout << "dup msg " << endl;
//         sendDelayed(msgg,0.01,"out");
//         out = 2;
//         //msg_seqno++;
//     }
//
//     return out;
//}
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
string Node::calculateCRC(string binaryStr){




                /*
                //append zeros at last of string
                for(int i=0;i<generator.length()-1;i++)
                {
                    binaryStr+='0';
                }
                cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                */
                //Division

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
        cout << "DDDDDDDDDDDDDD   " << getName() << endl;
        //LOG FILE
        string m =  s +" : received self message to start/complete sending messages at time = " + to_string(t) ;
        EV << m <<endl;
        addtoLogFile(m);
         if( type == 4 )
         {
             string m2 = s + " : time out .. complete sending messages";
             EV << m2 <<endl;
             addtoLogFile(m2);
         }
         if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
         {
             cout << "Sender finish sending messages.." <<endl;
             // LOG FILE
             string s0= s +  " : finish sending frames at time = " + to_string(t);
             EV << s0 <<endl;
             addtoLogFile(s0);
             addtoLogFile("-----------------------");
             //int total_time =  simTime().dbl() - start_time;
             addtoLogFile("total transmission time = "+ to_string(simTime().dbl() - start_time));
             addtoLogFile("total number of transmissions  = "+ to_string(num_transmissions));
             //int tp = numb_correctmsgs / total_time;
             addtoLogFile("throughput of network = " + to_string(numb_correctmsgs / ( simTime().dbl() - start_time)));
             //HENAAAA

             return;
         }
         string error_msg = "";
         string error_msg_type = "";
         MyMessage_Base * msgg = new MyMessage_Base();
         msgg->setM_Type(1);
         msgg->setSeq_Num(msg_seqno);
         //byte stuffing
         msgg->setM_Payload(byteStuffing(messages[msg_seqno]).c_str());
         // The CRC byte is added to the message trailer field
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
         EV<<msgg->getM_Payload()<<endl;
         string curr_error = errors[msg_seqno];
         // Errors
         //int check = checkErrorsType();
         int out = -1;
         //out = 0 -> loss
         // out = 1 -> delayed
         // out = 2 -> dup
         /// out = 3 -> dup w delay
         cout << "ERROR IS :" << curr_error <<endl;
         // curr_error = 1101
         char mod_error = curr_error[0];
         char loss_error = curr_error[1];
         char dup_error = curr_error[2];
         char delay_error = curr_error[3];
          if(loss_error == '1') //skip this message
          {
              double t = simTime().dbl();
              const char* str=getName();
              std::string s = str;
              error_msg = s + " : drop message with id = " +  to_string(msg_seqno) +
                      " and content = " +  msgg->getM_Payload() +
                        "and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " +  to_string(t);
              cout << "loss msg" <<endl;
              addtoLogFile(error_msg);
              out = 0;
              msg_seqno++;
              //schedule new event to complete (Self message )
              msgg->setM_Type(4);
             //msgg->piggybackingID(mmsg->piggybackingID());
              scheduleAt(simTime()+5, msgg);
              num_transmissions++;
          }
          if(mod_error == '1')
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
          if(delay_error == '1')
          {
              cout << "delayed msg " << endl;
              error_msg_type = error_msg_type + " with delay ";
              double t = simTime().dbl();

              const char* str=getName();
              std::string s = str;
              error_msg = s + ":  send msg with id = "+  to_string(msg_seqno) +
                                 " and content = " +msgg->getM_Payload() + "will be delayed" +
                                 "and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t)  ;
              addtoLogFile(error_msg);
              MyMessage_Base * msg_s = new MyMessage_Base();
              msg_s->setSeq_Num(msgg->getSeq_Num());
              msg_s->setM_Type(msgg->getM_Type());
              msg_s->setM_Payload( msgg->getM_Payload());
              msg_s->setpiggybackingID( msgg->getpiggybackingID());
              // The CRC byte is added to the message trailer field
              string Payload=msg_s->getM_Payload();
                       string binaryStr="";
                                       for (int i = 0; i < Payload.length(); i++)
                                       {
                                               bitset<8> binaryBits(Payload[i]);
                                               binaryStr+=binaryBits.to_string();
                                       }
                                       cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                       string CRCStr=calculateCRC(binaryStr);
              bits CRCbits(CRCStr);

              msg_s->setMycheckbits(CRCbits);

              sendDelayed(msg_s,delayy,"out"); // delay in second from ini file
              msg_seqno++;
              num_transmissions++;
              out = 1;
          }
          if(dup_error == '1')
          {
              cout << "dup msg " << endl;
              error_msg_type = error_msg_type + " with Duplication ";
              MyMessage_Base * msg_s = new MyMessage_Base();
              msg_s->setSeq_Num(msgg->getSeq_Num());
              msg_s->setM_Type(msgg->getM_Type());
              msg_s->setM_Payload( msgg->getM_Payload());
              msg_s->setpiggybackingID( msgg->getpiggybackingID());
              string Payload=msg_s->getM_Payload();
                                     string binaryStr="";
                                                     for (int i = 0; i < Payload.length(); i++)
                                                     {
                                                             bitset<8> binaryBits(Payload[i]);
                                                             binaryStr+=binaryBits.to_string();
                                                     }
                                                     cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                                     string CRCStr=calculateCRC(binaryStr);
                            bits CRCbits(CRCStr);

                            msg_s->setMycheckbits(CRCbits);
EV << " AHUU H3ML SCHEDULE to send dupp att "  << simTime() + 0.01  << endl;
num_transmissions++;
              sendDelayed(msg_s, 0.01,"out");
              out = 2;
              //msg_seqno++;
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
             send(msgg,"out"); // dup w delay m3 b3d???
             num_transmissions++;
             msg_seqno++;
         }
         // done send msg
         EV << error_msg ; //LOG FILE

    }
    else if( type == 0  ) // message from coordinator to any node (Sender/receiver)
    {
        if(start != -1 ) // if node is sender then read file
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

             const char* str1=getName();
             std::string s1 = str1;
             string m4 = s1 + " : finished reading from file...";
             EV << m4 << endl;
             addtoLogFile(m4);
             cout << "Sender node finish reading from file" <<endl;
             // Self message with start time
             MyMessage_Base * msg_s = new MyMessage_Base();
             msg_s->setSeq_Num(start);
             msg_s->setM_Type(type);
             msg_s->setM_Payload("Start sending..");
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
        else // msg from coordinator to receiver
        {
            //receiver
            // LOG FILE
            const char* str=getName();
            std::string s = str;
            intializeLogFile(s);
            string m4 = s + " : received msg from coordinator...";
            EV << m4 << endl;
            addtoLogFile(m4);
            sender = false;
        }

    }
    else if( type == 1  )// receiver receive data message from the other node
    {
        string mymsg = mmsg->getM_Payload();
        string characterCRC = (mmsg->getMycheckbits()).to_string();

        //unsigned char crc = static_cast<unsigned char>( characterCRC );
        //string crcbits=(mmsg->getMycheckbits()).to_string();
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
        EV <<"Receiver get msg from the other node with payload before de stuffing = " << mymsg << endl;
        EV <<"Receiver get msg from the other node with payload after de stuffing = " << final_msg<< endl;
        cout << " Node received message and will send ACK or NACK"<<endl;
        //cout << " message before de-stuffing "<< mymsg <<endl;
        cout << " message received after de-stuffing "<< final_msg <<endl;
        // Detect errors



        if(mmsg->getSeq_Num() < msg_ack )
        {
            err_typee = 5;
            //LOG FILE
            double t = simTime().dbl();
            const char* str=getName();
            std::string s = str;

            error_msg = s + " : drop  duplicated message with id = " +to_string(mmsg->getSeq_Num()) +" with content = "+ final_msg
                    + " at time = " + to_string(t);
            cout << "Receiver Dup frame .. discard frame " <<endl;
            // msh hn3ml haga hya kdakda duplicated message
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(err_typee);
            msg1->setpiggybackingID(msg_ack);
            sendDelayed(msg1,0.2,"out");//send(msg1,"out");
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
            msg_ack++;
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(err_typee);
            msg1->setpiggybackingID(msg_ack);
            sendDelayed(msg1,0.2,"out");//send(msg1,"out");
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
            msg_ack++;
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(err_typee);
            msg1->setpiggybackingID(msg_ack);
            sendDelayed(msg1,0.2,"out");//send(msg1,"out");
        }

        // LOG FILE  //+ simTime() +
        EV << error_msg <<endl;
        addtoLogFile(error_msg);
    }
    else if (type == 2 || type == 3 || type == 5)
    {
        // ACK or NACK from receiver to sender
        // ACK OR NACK = true
        string error_msg = "";
        string error_msg_type = "";
        double t = simTime().dbl();
        const char* str=getName();
        std::string s = str;
        cout << "Sender: Received ACK/NACK from receiver = " << mmsg->getpiggybackingID()  <<endl;
        if(type == 2)
        {
           string ss=
               s +  " : received ACK = " + to_string(type) + " at time = " + to_string(t) ;
           EV << ss;
           numb_correctmsgs++;
           addtoLogFile(ss);
        }
        else if ( type == 3)
        {
            //sender receive nack
            string ss=
                s +  " : received NACK = " + to_string(type) + " at time = " + to_string(t);
            EV << ss;
            addtoLogFile(ss);
        }

        if (mmsg->getpiggybackingID() < msg_seqno || type == 5)
        {
            //discard ACK
            string s2 = s + " : get NACK from (dup msg) , with piggybacking id =  " + to_string(mmsg->getpiggybackingID())  + " at time = " +  to_string(t);
            EV <<   s2 <<endl;
            addtoLogFile(s2);
            cout << "Sender:Delayed or dup ACK .. dicard ACK .. send new frame " <<endl;
            if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
            {
                cout << "Sender finish sending messages.." <<endl;
                // LOG FILE
                string s0= s +  " : finish sending frames at time = " + to_string(t);
                EV << s0 <<endl;
                addtoLogFile(s0);
                addtoLogFile("-----------------------");
                //int total_time =  simTime().dbl() - start_time;
                addtoLogFile("total transmission time = "+ to_string(simTime().dbl() - start_time));
                addtoLogFile("total number of transmissions  = "+ to_string(num_transmissions));
                //int tp = numb_correctmsgs / total_time;
                addtoLogFile("throughput of network = " + to_string(numb_correctmsgs / ( simTime().dbl() - start_time)));
                //HENAAAA
                return;
            }
        }
        else
        {
            /// add fl self msg
                cout << "Sender:will send new frame" <<endl;
            if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
            {
                cout << "Sender finish sending messages.." <<endl;
                // LOG FILE
                string s0= s +  " : finish sending frames at time = " + to_string(t);
                EV << s0 <<endl;
                addtoLogFile(s0);
                addtoLogFile("-----------------------");
                //int total_time =  simTime().dbl() - start_time;
                addtoLogFile("total transmission time = "+ to_string(simTime().dbl() - start_time));
                addtoLogFile("total number of transmissions  = "+ to_string(num_transmissions));
                //int tp = numb_correctmsgs / total_time;
                addtoLogFile("throughput of network = " + to_string(numb_correctmsgs / ( simTime().dbl() - start_time)));
                //HENAAAA

                return;
            }

            MyMessage_Base * msgg = new MyMessage_Base();
                     msgg->setM_Type(1);
                     msgg->setSeq_Num(msg_seqno);
                     //byte stuffing
                     msgg->setM_Payload(byteStuffing(messages[msg_seqno]).c_str());

                     EV<<msgg->getM_Payload()<<endl;
                     string binaryStr="";
                     string Payload=msgg->getM_Payload();
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
                                      //cout<<CRCbits<<endl;
                                      msgg->setMycheckbits(CRCbits);

                     msgg->setpiggybackingID(mmsg->getpiggybackingID());

                     string curr_error = errors[msg_seqno];
                     // Errors
                     //int check = checkErrorsType();
                     int out = -1;
                     //out = 0 -> loss
                     // out = 1 -> delayed
                     // out = 2 -> dup
                     /// out = 3 -> dup w delay
                     cout << "ERROR IS :" << curr_error <<endl;
                     // curr_error = 1101
                     char mod_error = curr_error[0];
                     char loss_error = curr_error[1];
                     char dup_error = curr_error[2];
                     char delay_error = curr_error[3];
                      if(loss_error == '1') //skip this message
                      {
                          double t = simTime().dbl();
                          cout << "loss msg" <<endl;
                          EV << "Sender: Message will be loss " <<endl;

                          const char* str=getName();
                          std::string s = str;
                          error_msg =  s + " : drop message with id = " +  to_string(msg_seqno) +
                                  " and content = " +  msgg->getM_Payload() +
                                    "and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t);
                          addtoLogFile(error_msg);
                          out = 0;
                          msg_seqno++;
                          msgg->setM_Type(4);
                          scheduleAt(simTime()+5, msgg);
                          num_transmissions++;
                      }
                      if(mod_error == '1')
                      {
                           cout << "modi msg " << endl;
                           error_msg_type =error_msg_type + " Modification ";
                           EV << "Sender : msg will de modified" <<endl;
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
                      if(delay_error == '1')
                      {
                          cout << "delayed msg " << endl;
                          error_msg_type = error_msg_type + " with delay ";
                          double t = simTime().dbl();

                          const char* str=getName();
                          std::string s = str;
                          error_msg = s + "  : send msg with id = "+ to_string( msg_seqno) + error_msg_type   +
                                             " and content = " +msgg->getM_Payload() + " will be delayed" +
                                             " and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t) + "." ;

                          MyMessage_Base * msg_s = new MyMessage_Base();
                          msg_s->setSeq_Num(msgg->getSeq_Num());
                          msg_s->setM_Type(msgg->getM_Type());
                          msg_s->setM_Payload( msgg->getM_Payload());
                          msg_s->setpiggybackingID( msgg->getpiggybackingID());
                          // The CRC byte is added to the message trailer field
                          string binaryStr="";
                                               string Payload=msg_s->getM_Payload();
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
                                                                //cout<<CRCbits<<endl;
                                                                msg_s->setMycheckbits(CRCbits);

                          addtoLogFile(error_msg);
                          sendDelayed(msg_s,delayy,"out"); // delay in second from ini file
                          msg_seqno++;
                          num_transmissions++;
                          out = 1;
                      }
                      if(dup_error == '1')
                      {
                          error_msg_type = error_msg_type + "  with Duplication  ";
                          MyMessage_Base * msg_s = new MyMessage_Base();
                          msg_s->setSeq_Num(msgg->getSeq_Num());
                          msg_s->setM_Type(msgg->getM_Type());
                          msg_s->setM_Payload( msgg->getM_Payload());
                          msg_s->setpiggybackingID( msgg->getpiggybackingID());

                          string Payload=msg_s->getM_Payload();
                                                               string binaryStr="";
                                                                               for (int i = 0; i < Payload.length(); i++)
                                                                               {
                                                                                       bitset<8> binaryBits(Payload[i]);
                                                                                       binaryStr+=binaryBits.to_string();
                                                                               }
                                                                               cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                                                               string CRCStr=calculateCRC(binaryStr);
                                                      bits CRCbits(CRCStr);

                                                      msg_s->setMycheckbits(CRCbits);

                          //bits CRCbits(calculateCRC(msgg->getM_Payload()));
                          //msg_s->setMycheckbits(CRCbits);
                          num_transmissions++;
                          sendDelayed(msg_s, 0.01,"out");
                          out = 2;
                          //msg_seqno++;
                      }
                     if (out != 0 && out != 1) // not loss msg and not delayed msg
                     {
                         //int t = omnetpp::SimTime();
                         double t = simTime().dbl();

                         const char* str=getName();
                         std::string s = str;

                         error_msg =  s + " : will send msg with id = "+  to_string(msg_seqno) +
                                            " and content = " + msgg->getM_Payload()+ "  " + error_msg_type +
                                            " and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " + to_string(t) + "." ;

                         addtoLogFile(error_msg);
                         cout << "sending msg" <<endl;
                         send(msgg,"out"); // dup w delay m3 b3d???
                         num_transmissions++;
                         msg_seqno++;
                     }

                     EV <<"Sender node send new message with msg_seqnumber = " << msgg->getSeq_Num() << endl;
                          // done send msg
                          EV << error_msg ;
        }
    }


}
