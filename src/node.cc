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
        string binaryStr="";
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

                cout<<stoi(str);

        //‘(x<<y)’ is equivalent to multiplying x with 2^y (2 raised to power y)

                return str;
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    int start = mmsg->getSeq_Num();
    int type = mmsg->getM_Type();
    if(msg->isSelfMessage()) // self message only for duplicte messages
    {
        //used for duplicated
        MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
        cout << " will send duplicant message" << endl;
        send(mmsg,"out");
        // wait???????????
    }
    else if( type == 0  ) // message from coordinator to any node (Sender/reciver)
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
                 MyMessage_Base * msgg = new MyMessage_Base();
                 msgg->setM_Type(1);
                 msgg->setSeq_Num(0);
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
                 //cout << "Node send message before byte stuffing: " << msg_input <<endl;
                 cout << "Node will send message after byte stuffing : " << final_payload <<endl;
                 // Errors
                 string curr_error = errors[i];
                 cout << "ERROR IS :" << curr_error <<endl;
                 // curr_error = 1101
                 char mod_error = curr_error[0];
                 char loss_error = curr_error[1];
                 char dup_error = curr_error[2];
                 char delay_error = curr_error[3];
                 if(loss_error == '1') //skip this message
                 {
                     cout << "loss msg " << endl;
                     continue;
                 }

                 if(mod_error == '1')
                 {
                     cout << "modi msg " << endl;
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
                     //sendDelayed(msgg,0.2,"out"); // delay in second from ini file
                 }
                 if(dup_error == '1')
                 {
                     cout << "dup msg " << endl;
                     MyMessage_Base * msg_s = new MyMessage_Base();
                     msg_s->setSeq_Num(msgg->getSeq_Num());
                     msg_s->setM_Type(msgg->getM_Type());
                     msg_s->setM_Payload( msgg->getM_Payload());
                     scheduleAt(simTime() + 0.01, msg_s);
                 }
                   send(msgg,"out");
                 // wait for ACK ?????????????????
             }

        }
        else // msg from coordintor to receiver
        {
            //receiver
            sender = false;
        }

    }
    else if( type == 1  )// receiver receive data message from the other node
    {
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
        //cout << " message before de-stuffing "<< mymsg <<endl;
        cout << " message after de-stuffing "<< final_msg <<endl;
        // Detect errors
        // send ACK
         MyMessage_Base * msg1 = new MyMessage_Base(" ");
         msg1->setM_Type(2);
         msg1->setSeq_Num(0);
         cout << "SSSSS" <<endl;
         send(msg1,"out");
    }
    else if (type == 2 || type == 3)
    {
        // ACK or NACK from receiver to sender
        // ACK OR NACK = true
        cout << "Received ACK/NACK " <<endl;
    }


}
