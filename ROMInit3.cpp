//Author: Darryl Beckham

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <algorithm>

using namespace std;

class ControlSignals
{

  public:
    //unsigned int signalArray[15];
  
      string RegWriteAddress;
      string RegWrite;
      string ALUSrcA;
      string ALUSrcB0;
      string ALUSrcB1;
      string MemWrite;
      string MemRead;
      string PCWriteCond;
      string PCWrite;
      string IorD;
      string IRWrite;
      string MemtoReg;
      string Jump;
      string JAL;
      string JR;
      string PCOut;

      // ALU OP bits
      string ALUOp3;
      string ALUOp2;
      string ALUOp1;
      string ALUOp0;

      string RegDst;
      string IROut;
      string PCSource0;
      string PCSource1;

      // next state bits
      string NS0;
      string NS1;
      string NS2; 
      string NS3;

    ControlSignals()
    {

      RegWriteAddress = "0";
      RegWrite = "0";
      ALUSrcA = "0";
      ALUSrcB1 = "0";
      ALUSrcB0 = "0";
      MemWrite = "0";
      MemRead = "0";
      PCWriteCond = "0";
      PCWrite = "0";
      IorD = "0";
      IRWrite = "0";
      MemtoReg = "0";
      Jump = "0";
      JAL = "0";
      JR = "0";
      PCOut = "0";
      ALUOp3 = "0";
      ALUOp2 = "0";
      ALUOp1 = "0";
      ALUOp0 = "0";
      RegDst = "0";
      IROut = "0";
      PCSource1 = "0";
      PCSource0 = "0";
      NS0 = "0";
      NS1 = "0";
      NS2 = "0";
      NS3 = "0";

    }

  protected:
    friend ostream& operator<< (ostream& out, ControlSignals signals);

};

ostream& operator<< (ostream& out, ControlSignals signals)
{

  string str = "";

  str.append(signals.NS3);
  str.append(signals.NS2);
  str.append(signals.NS1);
  str.append(signals.NS0);
  str.append(signals.PCSource1);
  str.append(signals.PCSource0);
  str.append(signals.IROut);
  str.append(signals.RegDst);
  str.append(signals.ALUOp0);
  str.append(signals.ALUOp1);
  str.append(signals.ALUOp2);
  str.append(signals.ALUOp3);
  str.append(signals.PCOut);
  str.append(signals.JR);
  str.append(signals.JAL);
  str.append(signals.Jump);
  str.append(signals.MemtoReg);
  str.append(signals.IRWrite);
  str.append(signals.IorD);
  str.append(signals.PCWrite);
  str.append(signals.PCWriteCond);
  str.append(signals.MemRead);
  str.append(signals.MemWrite);
  str.append(signals.ALUSrcB1);
  str.append(signals.ALUSrcB0);
  str.append(signals.ALUSrcA);
  str.append(signals.RegWrite);
  str.append(signals.RegWriteAddress);

  char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
                    '9', 'a', 'b', 'c', 'd', 'e', 'f' };

  string hexStr = "";
  size_t *index = 0;

  while (str.length() > 3)
  {
    string substr = str.substr(str.length()-4);
    str.erase(str.length()-4);
    
    int hex = stoi(substr, index, 2);
    char c = hexmap[hex];
    hexStr += c;
  }

  if (str.length() != 0)
  {
    int hex = stoi(str, index, 2);
    hexStr += hexmap[hex];
  }

  reverse(hexStr.begin(), hexStr.end());

  out << hexStr;

  return out;

}

void getRomValuesForSignals(string stateBits, ControlSignals *signals)
{

  int currentState = stoi(stateBits, nullptr, 2);

  switch (currentState)
  {
    case 0:
      signals->PCWrite = "1";
      signals->MemRead = "1";
      signals->IRWrite = "1";
      signals->PCSource0 = "1";
      signals->PCSource1 = "0";
      signals->ALUSrcB0 = "1";
      signals->ALUSrcB1 = "0";

      signals->ALUOp0 = "0";
      signals->ALUOp1 = "1";
      
      break;

    case 1:
      signals->ALUSrcB0 = "1";
      signals->ALUSrcB1 = "1";

      signals->ALUOp0 = "0";
      signals->ALUOp1 = "1";
      
      break;

    case 2:

      signa
    
    case 3:

      signals->ALUSrcA = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "0";

      signals->PCSource0 = "1";
      signals->PCSource1 = "0";
      break;

    case 4:
      signals->PCSource0 = "1";
      signals->PCSource1 = "1";
      signals->PCWriteCond = "1";

    case 10:
      signals->ALUSrcA = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "1";
      
      signals->PCSource0 = "1";
      signals->PCSource1 = "0";

      break;

    case 11:
      signals->RegWrite = "1";
      break;

    case 8:
      signals->RegWriteAddress = "1";
      signals->RegWrite = "1";
      break;

    default:
      break;

  }

}

void getRomValuesForNextState(string opCodeBits, string stateBits, ControlSignals *signals)
{

  // states:
  // 0 = fetch
  // 1 = decode
  // 2 = memory address coputation
  // 3 = execute r type
  // 4 = branch completion
  // 5 = jump completion
  // 6 = memory access for load word
  // 7 = memory access for store word
  // 8 = r type completion
  // 9 = write back step for load word
  // 10 = immediate execute
  // 11 = write reg for immediate 
  //
  
  int currentState = stoi(stateBits, nullptr, 2);

  // opcodebits
  // 000000 = r format = 0
  // 001000 = i immediate = 8

  int opCode = stoi(opCodeBits, nullptr, 2);

  if (currentState == 0)
  {
    signals->NS3 = "0";
    signals->NS2 = "0";
    signals->NS1 = "0";
    signals->NS0 = "1";

  }
  else if (currentState == 1)
  {
    if (opCode == 0)
    {
      signals->NS3 = "0";
      signals->NS2 = "0";
      signals->NS1 = "1";
      signals->NS0 = "1";
    }
    else if (opCode == 8 || opCode == 13 || opCode == 12)
    {
      signals->NS3 = "1";
      signals->NS2 = "0";
      signals->NS1 = "1";
      signals->NS0 = "0";
    }
    else if (opCode == 4)
    {

      signals->NS3 = "0";
      signals->NS2 = "1";
      signals->NS1 = "0";
      signals->NS0 = "0";

    }
    else if (opCode == 35)
    {

      signals->NS3 = "0";
      signals->NS2 = "0";
      signals->NS1 = "1";
      signals->NS0 = "0";

    }

  }
  else if (currentState == 3)
  {
      signals->NS3 = "1";
      signals->NS2 = "0";
      signals->NS1 = "0";
      signals->NS0 = "0";
  }
  else if(currentState == 8)
  {

      signals->NS3 = "0";
      signals->NS2 = "0";
      signals->NS1 = "0";
      signals->NS0 = "0";

  }
  else if (currentState == 10)
  {

      signals->NS3 = "1";
      signals->NS2 = "0";
      signals->NS1 = "1";
      signals->NS0 = "1";

  }
  else if (currentState == 11)
  {
      signals->NS3 = "0";
      signals->NS2 = "0";
      signals->NS1 = "0";
      signals->NS0 = "0";
  }


}

int main(int argc, char* argv[])
{

  int index = 0;
  ofstream file;
  file.open("ROMInit.txt");


  string header = "RegWriteAddress,RegWrite,ALUSrcA,ALUSrcB1,ALUSrcB0,MemWrite,MemRead,PCWriteCond,PCWrite,IorD,IRWrite,MemtoReg,JAL,JR,PCOut,ALUOp3,ALUOp2,ALUOp1,ALUOp0,RegDst,IROut";
  string header2 = "v2.0 raw";

  file << header2 << endl;

  for (int i = 0; i < 1024; i++)
  {

    string address = bitset< 10 >( i ).to_string();

    string stateBits = address.substr(address.length()-4);
    address.erase(address.length()-4);

    string opCodeBits = address;

    ControlSignals signals = ControlSignals();

    getRomValuesForSignals(stateBits, &signals);
    getRomValuesForNextState(opCodeBits, stateBits, &signals);

    file << signals;
    index++;

    if (index == 7)
    {
      file << endl;
      index = 0;
    }
    else
      file << " ";

  }

  return 0;

}
