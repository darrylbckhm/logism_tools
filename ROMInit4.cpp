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

    }

  protected:
    friend ostream& operator<< (ostream& out, ControlSignals signals);

};

ostream& operator<< (ostream& out, ControlSignals signals)
{

  string str = "";

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

void getRomValuesForSignals(string opCodeBits, ControlSignals *signals)
{

  int opCode = stoi(opCodeBits, nullptr, 2);

  switch (opCode)
  {
    case 0: // R-type instruction w/ funct field
      signals->RegWrite = "1";
      signals->RegWriteAddress = "1";
      break;

    case 1:
      break;

    case 2: // J
      //signals->
      break;
    
    case 3: // JAL
      break;

    case 4:
      break;

    case 5:
      break;

    case 6:
      break;

    case 7:
      break;

    case 8: // ADDI
      signals->RegWrite = "1";
      signals->IorD = "1";
      signals->ALUOp0 = "1";
      signals->ALUOp1 = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "1";

    case 9:
      break;

    case 10:
      break;

    case 11: 
      break;

    case 12: // ANDI
      signals->RegWrite = "1";
      signals->IorD = "1";
      signals->ALUOp1 = "1";
      signals->ALUOp2 = "1";
      break;

    case 13: // ORI
      signals->RegWrite = "1";
      signals->IorD = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "1";
      break;

    case 35: // LW
      signals->MemtoReg = "1";
      signals->RegWrite = "1";
      signals->MemRead = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "1";
      signals->ALUOp0 = "1";
      signals->ALUOp1 = "1";
      break;

    case 43: // SW
      signals->MemWrite = "1";
      signals->ALUSrcB0 = "0";
      signals->ALUSrcB1 = "1";
      signals->ALUOp0 = "1";
      signals->ALUOp1 = "1";
      break;

    default:
      break;

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

  for (int i = 0; i < 64; i++)
  {

    string address = bitset< 6 >( i ).to_string();

    string opCodeBits = address;

    ControlSignals signals = ControlSignals();

    getRomValuesForSignals(opCodeBits, &signals);

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
