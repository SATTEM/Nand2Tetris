#ifndef VMFILE_CPP
#define VMFILE_CPP
#include "Command/Factory.hpp"
#include "Command/MemoryCommand.hpp"
#include "Command/PlainCommand.hpp"
#include "CommonFile.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
namespace VM{
	class VMFile:public CommonFile{
	//VM代码文件
	public:
		VMFile(std::fstream& fs):CommonFile(fs){
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
			//注册所有工厂
			factories_["push"]=std::make_unique<ConcreteFactory<PushCommand>>();//注册push
			factories_["pop"]=std::make_unique<ConcreteFactory<PopCommand>>();//注册pop
			factories_["add"]=std::make_unique<ConcreteFactory<AddCommand>>();//注册add
			factories_["sub"]=std::make_unique<ConcreteFactory<SubCommand>>();//注册sub
			factories_["neg"]=std::make_unique<ConcreteFactory<NegCommand>>();//注册neg
			factories_["or"]=std::make_unique<ConcreteFactory<OrCommand>>();//注册or
			factories_["not"]=std::make_unique<ConcreteFactory<NotCommand>>();//注册not
			factories_["add"]=std::make_unique<ConcreteFactory<AddCommand>>();//注册and
			factories_["eq"]=std::make_unique<ConcreteFactory<EqCommand>>();//注册eq
			factories_["lt"]=std::make_unique<ConcreteFactory<LtCommand>>();//注册lt
			factories_["Gt"]=std::make_unique<ConcreteFactory<GtCommand>>();//注册gt
		}
		virtual ~VMFile()=default;
		std::string Compile()override{
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
	private:
		std::list<std::string>::iterator iter_;
		std::unordered_map<std::string, std::unique_ptr<CommandFactory>> factories_;
	};
}
#endif