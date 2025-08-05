#include "Command/PlainCommand.hpp"
#include <string>
using std::string;
using namespace VM;
string AddCommand::Compile()const{
	return "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nM=D+M\n";
}
string AndCommand::Compile()const{
	return "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nM=D&M\n";
}
string NotCommand::Compile()const{
	return "@SP\nA=M-1\nM=!M\n";
}
string NegCommand::Compile()const{
	return "@SP\nA=M-1\nM=-M\n";
}
string SubCommand::Compile()const{
	return "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nM=M-D\n";
}
string OrCommand::Compile()const{
	return "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nM=D|M\n";
}
string GtCommand::Compile()const{
    static int gt_count = 0;
    gt_count++;
    string label_prefix = current_function_name_ + "_GT_" + std::to_string(gt_count);
    
    return 
    "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nD=M-D\n"
    "@" + label_prefix + "_TRUE\n"
    "D;JGT\n"
    "@SP\nA=M-1\nM=0\n"
    "@" + label_prefix + "_END\n0;JMP\n"
    "(" + label_prefix + "_TRUE)\n"
    "@SP\nA=M-1\nM=-1\n"
    "(" + label_prefix + "_END)\n";
}
string LtCommand::Compile()const{
    static int lt_count = 0;
    lt_count++;
    string label_prefix = current_function_name_ + "_LT_" + std::to_string(lt_count);
    
    return 
    "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nD=M-D\n"
    "@" + label_prefix + "_TRUE\n"
    "D;JLT\n"
    "@SP\nA=M-1\nM=0\n"
    "@" + label_prefix + "_END\n0;JMP\n"
    "(" + label_prefix + "_TRUE)\n"
    "@SP\nA=M-1\nM=-1\n"
    "(" + label_prefix + "_END)\n";
}
string EqCommand::Compile()const{
    static int eq_count = 0;
    eq_count++;
    string label_prefix = current_function_name_ + "_EQ_" + std::to_string(eq_count);
    
    return 
    "@SP\nAM=M-1\nD=M\n@SP\nA=M-1\nD=M-D\n"
    "@" + label_prefix + "_TRUE\n"
    "D;JEQ\n"
    "@SP\nA=M-1\nM=0\n"
    "@" + label_prefix + "_END\n0;JMP\n"
    "(" + label_prefix + "_TRUE)\n"
    "@SP\nA=M-1\nM=-1\n"
    "(" + label_prefix + "_END)\n";
}