#include "File/VMFile.hpp"
#include <fstream>
#include <iostream>
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
std::string VMFile::Compile(){
//编译：提供代码段起点，每条命令按需获取代码，保证迭代器永远指向完整代码的起点
	std::string final_code="@256\nD=A\n@SP\nM=D\n\n";//初始化
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
	final_code+="(END)\n  @END\n0;JMP";
	return final_code;
}