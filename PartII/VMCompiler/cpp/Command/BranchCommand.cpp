#include "Command/BranchCommand.hpp"
#include <string>
using namespace VM;
std::string LabelCommand::Compile()const{
	std::string hack_code;
	hack_code+="("+label_+")\n";
	return hack_code;
}
std::string GotoCommand::Compile()const{
	std::string hack_code;
	hack_code+="@"+label_+"\n0;JMP\n";//无条件跳转
	return hack_code;
}
std::string IfGotoCommand::Compile()const{
	std::string hack_code;
	std::string pop_to_D="@SP\nM=M-1\nA=M\nD=M\n";
	hack_code+=pop_to_D;//提取条件
	hack_code+="@"+label_+"\nD;JNE\n";//若不为0，则条件为真跳转到label
	return hack_code;
}