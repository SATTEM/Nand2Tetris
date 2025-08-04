#include "Command/PlainCommand.hpp"
#include <string>
using std::string;
using namespace VM;
string AddCommand::Compile()const{
	return "@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nM=D+M\n";
}
string AndCommand::Compile()const{
	return "@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nM=D&M\n";
}
string NotCommand::Compile()const{
	return "@SP\nA=M-1\nM=!M\n";
}
string NegCommand::Compile()const{
	return "@SP\nA=M-1\nM=-M\n";
}
string SubCommand::Compile()const{
	return "@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nM=M-D\n";
}
string OrCommand::Compile()const{
	return "@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nM=D|M\n";
}
string GtCommand::Compile()const{
	return 
	"@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nD=M-D\n@32767\n"
	"A=A+1\nD=D&A\nD=D-A\n@SP\nA=M-1\nM=D\n";
}
string LtCommand::Compile()const{
	return 
	"@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nD=D-M\n@32767\n"
	"A=A+1\nD=D&A\nD=D-A\n@SP\nA=M-1\nM=D\n";
}
string EqCommand::Compile()const{
	return "@SP\nM=M-1\nA=M\nD=M\n@SP\nA=M-1\nM=D-M\n";
}