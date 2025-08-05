#include "Command/FunctionCommand.hpp"
#include "Command/VMCommand.hpp"
#include "File/VMFile.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
using namespace VM;
VMFile::VMFile(std::fstream& fs):CommonFile(fs){
	std::list<std::string> tmp;
	for(auto str:file_){
		std::stringstream ss(str);
		std::string t;
		while(ss>>t){
			tmp.push_back(t);
		}
	}
	file_=tmp;//将每行代码分割成代码段
	iter_=file_.begin();
}
std::string VMFile::Compile(const bool is_main){
//编译：提供代码段起点，每条命令按需获取代码，保证迭代器永远指向完整代码的起点
	std::string final_code;
	if(is_main){
		final_code="@256\nD=A\n@SP\nM=D\n\n";//初始化栈
		std::list<std::string> call_sys_init={"call","Sys.init","0"};//初始化启动函数
		auto sys_init_iter=call_sys_init.begin();
		final_code+=CallCommand(sys_init_iter).Compile();//在初始化栈之后立即调用Sys.init
		//final_code+="@Sys.init\n0;JMP\n";
		final_code+="(END)\n  @END\n0;JMP\n";//从Sys.init返回后进入无限循环
	}
	iter_=file_.begin();
	while(iter_!=file_.end()){
		if(factories_.find(*iter_)==factories_.end()){
			std::cerr<<"Invalid command!"<<std::endl;//若不是已注册命令
			break;
		}else{
			std::cout<<"["<<*iter_<<"] ";//否则输出正在处理的命令
		}
		final_code+=factories_[*iter_]->Produce(iter_)->Compile();//编译代码
		final_code+="\n";//每编译完一句完整的语句，添加分割
	}
	std::cout<<std::endl;//输出结束换行
	return final_code;
}