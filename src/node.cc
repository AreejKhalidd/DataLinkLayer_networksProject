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
// check hwar el random number lw h3mel add seedset fl ini

void Node::initialize()
{
    // TODO - Generated method body
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
string Node::calculateCRC(string M_Payload){

    string binaryStr="";
    //converting message to binary string
        for (int i = 0; i < M_Payload.length(); i++)
        {
                bitset<8> binaryBits(M_Payload[i]);
                binaryStr+=binaryBits.to_string();
        }
        //append zeros at last of string
        for(int i=0;i<generator.length();i++)
        {
            binaryStr+='0';
        }
        //Division
        //string binaryStr="";
            for (int i = 0; i < M_Payload.length(); i++)
            {
                    bitset<8> binaryBits(M_Payload[i]);
                    binaryStr+=binaryBits.to_string();
            }
                       cout<< binaryStr<<endl ;

                  string generator ="1001" ;
                for(int i=0;i<generator.length();i++)
                {
                    binaryStr+='0';
                }
                       cout<< binaryStr<<endl ;
                       /*
            long long int binaryArr=0;
                for (int i =M_Payload.length()-1 ; i >=0 ; i--)
                {
                        bitset<8> binaryBits(M_Payload[i]);
                        binaryArr=binaryArr >> (32);
                        binaryArr+=stoi(binaryBits.to_string());
                        cout<<binaryArr<<endl;
                }
                cout<<binaryArr;
               //cout<< stoi(binaryStr)  ;

        string str="";
        cout<<str.length();
        */
        //string M_Payload="";
        //string binaryStr="1110101010101010101010110010101011011";
        //string generator="1001";
            //converting message to binary string
                for (int i = 0; i < M_Payload.length(); i++)
                {
                        bitset<8> binaryBits(M_Payload[i]);
                        binaryStr+=binaryBits.to_string();
                }
                cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                //append zeros at last of string
                for(int i=0;i<generator.length()-1;i++)
                {
                    binaryStr+='0';
                }
                cout<<binaryStr <<"     "<<binaryStr.length()<<endl;
                //Division
                //int i=binaryStr.length();
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



        //‘(x<<y)’ is equivalent to multiplying x with 2^y (2 raised to power y)

                return str;
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    int start = mmsg->getSeq_Num();
    int type = mmsg->getM_Type();
    if(msg->isSelfMessage()) // self message to start send messages to receiver node
    {
         EV <<" Self message to sender node to start sending messages at time = " << simTime() << endl;
         string error_msg = "";
         string error_msg_type = "";
         MyMessage_Base * msgg = new MyMessage_Base();
         msgg->setM_Type(1);
         msgg->setSeq_Num(msg_seqno);
         //byte stuffing
         msgg->setM_Payload(byteStuffing(messages[msg_seqno]).c_str());
         // The CRC byte is added to the message trailer field
         string CRCStr=calculateCRC(msgg->getM_Payload());
         cout<<"CRC Bits: "<<CRCStr<<endl;
         EV<<"CRC Bits: "<<CRCStr<<endl;
         bits CRCbits(CRCStr);
         //cout<<CRCbits<<endl;
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
              error_msg = "Sender drop message with id = " +  to_string(msg_seqno) ;
              cout << "loss msg" <<endl;
              out = 0;
              msg_seqno++;
          }
          if(mod_error == '1')
          {
               cout << "modi msg " << endl;
               error_msg_type = "Modification";
               int index=uniform(0,1)*10;
               const char* str = msgg->getM_Payload();
               string s = str;
               int size = s.size();
               while (index > size-1)
               {
                   index=uniform(0,1)*10;
               }
               string mypayload= msgg->getM_Payload();
               mypayload[index]=mypayload[index]+5;
               msgg->setM_Payload(mypayload.c_str());
               cout << "msg after modi " << msgg->getM_Payload() <<endl;

          }
          if(delay_error == '1')
          {
              cout << "delayed msg " << endl;
              error_msg = "Sender will send msg with id = "+  to_string(msg_seqno) +
                                 " and content = " +msgg->getM_Payload() + "will be delayed" +
                                 "and piggy backing ACK ="+  to_string(0) +"at time = " ;//+  to_string(simTime()) + "." ;

              MyMessage_Base * msg_s = new MyMessage_Base();
              msg_s->setSeq_Num(msgg->getSeq_Num());
              msg_s->setM_Type(msgg->getM_Type());
              msg_s->setM_Payload( msgg->getM_Payload());
              msg_s->setpiggybackingID( msgg->getpiggybackingID());
              sendDelayed(msg_s,0.2,"out"); // delay in second from ini file
              msg_seqno++;
              out = 1;
          }
          if(dup_error == '1')
          {
              cout << "dup msg " << endl;
              error_msg_type = "will be duplicated";
              MyMessage_Base * msg_s = new MyMessage_Base();
              msg_s->setSeq_Num(msgg->getSeq_Num());
              msg_s->setM_Type(msgg->getM_Type());
              msg_s->setM_Payload( msgg->getM_Payload());
              msg_s->setpiggybackingID( msgg->getpiggybackingID());

              sendDelayed(msg_s,simTime() + 0.01,"out");
              out = 2;
              //msg_seqno++;
          }
         if (out != 0 && out != 1) // not loss msg and not delayed msg
         {
             error_msg = "Sender will send msg with id = "+  to_string(msg_seqno) +
                     " and content = " +msgg->getM_Payload() + error_msg_type +
                     "and piggy backing ACK = "+  to_string(0) +" at time = " ;//+ simTime() + "." ;
             cout << "sending msg" <<endl;
             send(msgg,"out"); // dup w delay m3 b3d???
             msg_seqno++;
         }
         EV <<"Sender node send new message with msg_seqnumber = " << msgg->getSeq_Num() << endl;
         // done send msg
         EV << error_msg ;

    }
    else if( type == 0  ) // message from coordinator to any node (Sender/receiver)
    {
        if(start != -1 ) // if node is sender then read file
        {
            EV <<"Sender start reading from file" << endl;
            sender = true;
            cout << "Sender Node start to read data from file" <<endl;
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
             EV <<"Sender finished reading from file" << endl;
             cout << "Sender node finish reading from file" <<endl;
             // Self message with start time
             MyMessage_Base * msg_s = new MyMessage_Base();
             msg_s->setSeq_Num(start);
             msg_s->setM_Type(type);
             msg_s->setM_Payload("Start sending..");
             EV <<"Sender schedule self message" << endl;
             string CRCStr=calculateCRC(msg_s->getM_Payload());
             cout<<"CRC Bits: "<<CRCStr<<endl;
             EV<<"CRC Bits: "<<CRCStr<<endl;
             bits CRCbits(CRCStr);
             //cout<<CRCbits<<endl;
             msg_s->setMycheckbits(CRCbits);
             scheduleAt(start, msg_s);

        }
        else // msg from coordintor to receiver
        {
            //receiver
            EV <<"Receiver received msg from coordinator" << endl;
            sender = false;
        }

    }
    else if( type == 1  )// receiver receive data message from the other node
    {
        string mymsg = mmsg->getM_Payload();

        // Detect errors
        // send ACK
        int err_typee;
        string CRCStr=calculateCRC(mmsg->getM_Payload());
        cout<<"CRC Bits: "<<CRCStr<<endl;
        EV<<"CRC Bits: "<<CRCStr<<endl;
        bits CRCbits(CRCStr);

        bits sent=mmsg->getMycheckbits();
        if(sent==CRCbits)
            err_typee=2;// ACK no error
        else
            err_typee=3;// NACK error
        // de-stuffing
        string final_msg = deStuffing(mymsg);
        EV <<"Receiver received msg from the other node with payload after de stuffing = " << final_msg<< endl;
        cout << " Node received message and will send ACK or NACK"<<endl;
        //cout << " message before de-stuffing "<< mymsg <<endl;
        cout << " message received after de-stuffing "<< final_msg <<endl;



        if(mmsg->getSeq_Num() < msg_ack )
        {
            err_typee = 3;
            EV << "Receiver: received dup frame , discard frame , send same ACK = " << msg_ack <<endl;//msh fahma
            cout << "Receiver : Dup frame .. discard frame .. send same ACK" <<endl;
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(err_typee);
            msg1->setpiggybackingID(msg_ack);
            sendDelayed(msg1,0.2,"out");//send(msg1,"out");
        }
        else
        {
            msg_ack++;
            cout << "Receiver ..received frame .. send new ACK" << endl;
            EV << "Receiver get new frame , will send new ACK = " << msg_ack <<endl;
            MyMessage_Base * msg1 = new MyMessage_Base(" ");
            msg1->setM_Type(err_typee);
            msg1->setpiggybackingID(msg_ack);
            sendDelayed(msg1,0.2,"out");//send(msg1,"out");
        }

        string error_msg = "Receiver : received message with id = " + to_string( mmsg->getSeq_Num()) +
                " with content = " +  mmsg->getM_Payload() +
                " Piggy backing ACK  = " +  to_string(msg_ack-1) +" at time = " + "."; //+ simTime() +
        EV << error_msg <<endl;
    }
    else if (type == 2 || type == 3)
    {
        // ACK or NACK from receiver to sender
        // ACK OR NACK = true
        string error_msg = "";
        string error_msg_type = "";
        cout << "Sender: Received ACK/NACK from receiver = " << mmsg->getpiggybackingID()  <<endl;
        if (mmsg->getpiggybackingID() < msg_seqno)
        {
            //discard ACK
            EV << "Sender : get dup ACK , discard send new frame with seq = " << msg_seqno <<endl;
            cout << "Sender:Delayed or dup ACK .. dicard ACK .. send new frame " <<endl;
        }
        else
        {
            EV << "Sender : get new ack , send new msg with seq = " << msg_seqno << endl;
            cout << "Sender:will send new frame" <<endl;
        }
        if ( mmsg->getpiggybackingID() > messages.size()-1  || msg_seqno > messages.size()-1  )
        {
            cout << "Sender finish sending messages.." <<endl;
            EV << "Sender finish sending frames" <<endl;
        }
        MyMessage_Base * msgg = new MyMessage_Base();
                 msgg->setM_Type(1);
                 msgg->setSeq_Num(msg_seqno);
                 //byte stuffing
                 msgg->setM_Payload(byteStuffing(messages[msg_seqno]).c_str());
                 EV<<"AAAAAAAAAAAA"<<endl;
                 EV<<msgg->getM_Payload()<<endl;
                 string CRCStr=calculateCRC(msgg->getM_Payload());
                 cout<<"CRC Bits: "<<CRCStr<<endl;
                 EV<<"CRC Bits: "<<CRCStr<<endl;
                 bits CRCbits(CRCStr);
                 //cout<<CRCbits<<endl;
                 msgg->setMycheckbits(CRCbits);
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
                      cout << "loss msg" <<endl;
                      EV << "Sender: Message will be loss " <<endl;
                      error_msg = "Sender drop message with id = " +  to_string(msg_seqno) ;
                      out = 0;
                      msg_seqno++;
                  }
                  if(mod_error == '1')
                  {
                       cout << "modi msg " << endl;
                       error_msg_type = "Modification";
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
                       mypayload[index]=mypayload[index]+5;
                       msgg->setM_Payload(mypayload.c_str());
                       cout << "msg after modi " << msgg->getM_Payload() <<endl;
                  }
                  if(delay_error == '1')
                  {
                      EV <<"Sender: Message will be delayed" <<endl;
                      cout << "delayed msg " << endl;

                      error_msg = "Sender will send msg with id = "+ to_string( msg_seqno) +
                                         " and content = " +msgg->getM_Payload() + " will be delayed" +
                                         " and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " ;//+ simTime() + "." ;
                      sendDelayed(msgg,0.2,"out"); // delay in second from ini file
                      msg_seqno++;
                      out = 1;
                  }
                  if(dup_error == '1')
                  {
                      EV << "Sender: Message will be duplicated" << endl;
                      cout << "dup msg " << endl;

                      error_msg_type = " will be duplicated ";
                      sendDelayed(msgg,simTime() + 0.01,"out");
                      out = 2;
                      //msg_seqno++;
                  }
                 if (out != 0 && out != 1) // not loss msg and not delayed msg
                 {
                     error_msg = " Sender will send msg with id = "+  to_string(msg_seqno) +
                                        " and content = " +msgg->getM_Payload() + error_msg_type +
                                        " and piggy backing ACK ="+  to_string(mmsg->getpiggybackingID()) +" at time = " ;//-++  to_string(simTime()) + "." ;

                     cout << "sending msg" <<endl;
                     EV << "Sender will send msg" << endl;
                     send(msgg,"out"); // dup w delay m3 b3d???
                     msg_seqno++;
                 }

                 EV <<"Sender node send new message with msg_seqnumber = " << msgg->getSeq_Num() << endl;
                      // done send msg
                      EV << error_msg ;
    }


}
