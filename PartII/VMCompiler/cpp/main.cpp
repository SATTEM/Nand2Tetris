#include <fstream>
#include <ios>
#include <iostream>
#include "Command/MemoryCommand.hpp"
#include "File/VMFile.hpp"

	std::string VM::MemoryCommand::current_file_name_;
int main(int argc,char* argv[]){
	std::fstream in(argv[1],std::ios_base::in);
	VM::MemoryCommand::SetCurrentFileName(argv[1]);
	VM::VMFile vm(in);
	std::fstream out(argv[2],std::ios_base::out);
	out<<vm;
}