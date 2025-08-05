#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "Command/Factory.hpp"
#include "Command/BranchCommand.hpp"
#include "Command/Factory.hpp"
#include "Command/FunctionCommand.hpp"
#include "Command/VMCommand.hpp"
#include "Command/PlainCommand.hpp"
#include "Command/MemoryCommand.hpp"
#include "File/VMFile.hpp"

std::string VM::VMCommand::current_file_name_;
std::string VM::VMCommand::current_function_name_;
std::unordered_map<std::string, std::unique_ptr<VM::CommandFactory>> VM::VMFile::factories_;

void RegisterAllCommand();
std::string CompileOneFile(std::fstream& input,const bool is_main);
int main(int argc,char* argv[]){
	using namespace std::filesystem;
	std::string output,pure_name,code;
	RegisterAllCommand();
	if(argc!=2){std::cerr<<"Invalid argument!"<<std::endl;return -1;}
	path input_path(argv[1]);
	if(!exists(input_path)){
		std::cerr<<"Invalid input!"<<std::endl;
		return -1;
	}
	directory_entry entry(input_path);
	if(entry.status().type()==file_type::directory){
		//目录编译
		output="out.asm";
		directory_iterator dir(input_path);
		bool is_first=true;
		for(auto& it:dir){
			if(it.path().extension()!=".vm"){continue;}
			pure_name=it.path().stem();
			VM::VMCommand::SetCurrentFileName(pure_name);
			std::fstream fs(it.path(),std::ios_base::in);
			if(!fs){std::cerr<<"Fail to open"<<it.path()<<std::endl;return -1;}
			code+=CompileOneFile(fs, is_first);
			if(is_first){
				is_first=false;
			}
			fs.clear();
			fs.close();
		}
	}else {
		//单文件编译
		if(input_path.extension()!=".vm"){std::cerr<<"Input is not a vm file!"<<std::endl;return -1;}
		pure_name=input_path.stem();
		output=pure_name+".asm";
		VM::VMCommand::SetCurrentFileName(pure_name);
		std::fstream fs(input_path,std::ios_base::in);
		if(!fs){std::cerr<<"Fail to open "<<input_path<<std::endl;return -1;}
		code=CompileOneFile(fs,true);//单文件编译,则只有一个.vm文件
		fs.close();
	}
	std::fstream out(output,std::ios_base::out);
	out<<code;
	out.close();
}
void RegisterAllCommand(){
//注册所有工厂
	using namespace VM;
	VMFile::RegisterCommand("push",std::make_unique<ConcreteFactory<PushCommand>>());//注册push
	VMFile::RegisterCommand("pop",std::make_unique<ConcreteFactory<PopCommand>>());//注册pop
	VMFile::RegisterCommand("add",std::make_unique<ConcreteFactory<AddCommand>>());//注册add
	VMFile::RegisterCommand("sub",std::make_unique<ConcreteFactory<SubCommand>>());//注册sub
	VMFile::RegisterCommand("neg",std::make_unique<ConcreteFactory<NegCommand>>());//注册neg
	VMFile::RegisterCommand("or",std::make_unique<ConcreteFactory<OrCommand>>());//注册or
	VMFile::RegisterCommand("not",std::make_unique<ConcreteFactory<NotCommand>>());//注册not
	VMFile::RegisterCommand("add",std::make_unique<ConcreteFactory<AddCommand>>());//注册and
	VMFile::RegisterCommand("eq",std::make_unique<ConcreteFactory<EqCommand>>());//注册eq
	VMFile::RegisterCommand("lt",std::make_unique<ConcreteFactory<LtCommand>>());//注册lt
	VMFile::RegisterCommand("gt",std::make_unique<ConcreteFactory<GtCommand>>());//注册gt
	VMFile::RegisterCommand("label", std::make_unique<ConcreteFactory<LabelCommand>>());//注册label
	VMFile::RegisterCommand("goto", std::make_unique<ConcreteFactory<GotoCommand>>());//注册goto
	VMFile::RegisterCommand("if-goto", std::make_unique<ConcreteFactory<IfGotoCommand>>());//注册if-goto
	VMFile::RegisterCommand("function", std::make_unique<ConcreteFactory<FunctionClaimCommand>>());//注册function
	VMFile::RegisterCommand("call", std::make_unique<ConcreteFactory<CallCommand>>());//注册call
	VMFile::RegisterCommand("return", std::make_unique<ConcreteFactory<ReturnCommand>>());//注册return
}
std::string CompileOneFile(std::fstream& input,const bool is_main){
	VM::VMFile vm(input);
	return vm.Compile(is_main);
}