#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include "Command/MemoryCommand.hpp"
#include "File/VMFile.hpp"

	std::string VM::MemoryCommand::current_file_name_;
int main(int argc,char* argv[]){
	if(argc!=2){std::cerr<<"Compiler need ONE input parameter!"<<std::endl;return -1;}
	std::string input(argv[1]);
	if(input.find(".vm")==input.npos){std::cerr<<"Input is not a vm file!"<<std::endl;return -1;}
	std::string output=input.substr(0,input.find('.'))+".asm";
	VM::MemoryCommand::SetCurrentFileName(output);
	std::fstream in(input,std::ios_base::in);
	if(!in){std::cerr<<"Fail to open "<<input<<std::endl;return -1;}
	VM::VMFile vm(in);
	std::fstream out(output,std::ios_base::out);
	out<<vm;
	in.close();
	out.close();
}