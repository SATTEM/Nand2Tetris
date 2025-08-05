#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <string>
#include "Command/BranchCommand.hpp"
#include "Command/Factory.hpp"
#include "Command/VMCommand.hpp"
#include "Command/PlainCommand.hpp"
#include "Command/MemoryCommand.hpp"
#include "File/VMFile.hpp"

std::string VM::VMCommand::current_file_name_;
void RegisterAllCommand(VM::VMFile& file);
int main(int argc,char* argv[]){
	if(argc!=2){std::cerr<<"Compiler need ONE input parameter!"<<std::endl;return -1;}
	std::string input(argv[1]);
	if(input.find(".vm")==input.npos){std::cerr<<"Input is not a vm file!"<<std::endl;return -1;}
	std::string pure_name=input.substr(0,input.find('.'));
	std::string output=pure_name+".asm";
	VM::VMCommand::SetCurrentFileName(pure_name);
	std::fstream in(input,std::ios_base::in);
	if(!in){std::cerr<<"Fail to open "<<input<<std::endl;return -1;}
	VM::VMFile vm(in);
	RegisterAllCommand(vm);
	std::fstream out(output,std::ios_base::out);
	out<<vm;
	in.close();
	out.close();
}
void RegisterAllCommand(VM::VMFile& file){
			//注册所有工厂
			using namespace VM;
			file.RegisterCommand("push",std::make_unique<ConcreteFactory<PushCommand>>());//注册push
			file.RegisterCommand("pop",std::make_unique<ConcreteFactory<PopCommand>>());//注册pop
			file.RegisterCommand("add",std::make_unique<ConcreteFactory<AddCommand>>());//注册add
			file.RegisterCommand("sub",std::make_unique<ConcreteFactory<SubCommand>>());//注册sub
			file.RegisterCommand("neg",std::make_unique<ConcreteFactory<NegCommand>>());//注册neg
			file.RegisterCommand("or",std::make_unique<ConcreteFactory<OrCommand>>());//注册or
			file.RegisterCommand("not",std::make_unique<ConcreteFactory<NotCommand>>());//注册not
			file.RegisterCommand("add",std::make_unique<ConcreteFactory<AddCommand>>());//注册and
			file.RegisterCommand("eq",std::make_unique<ConcreteFactory<EqCommand>>());//注册eq
			file.RegisterCommand("lt",std::make_unique<ConcreteFactory<LtCommand>>());//注册lt
			file.RegisterCommand("gt",std::make_unique<ConcreteFactory<GtCommand>>());//注册gt
			file.RegisterCommand("label", std::make_unique<ConcreteFactory<LabelCommand>>());//注册label
			file.RegisterCommand("goto", std::make_unique<ConcreteFactory<GotoCommand>>());//注册goto
			file.RegisterCommand("if-goto", std::make_unique<ConcreteFactory<IfGotoCommand>>());//注册if-goto
}