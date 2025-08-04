#ifndef VMFILE_CPP
#define VMFILE_CPP
#include "Command/MemoryCommand.hpp"
#include "CommonFile.hpp"
#include <sstream>
#include <string>
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
		}
		virtual ~VMFile()=default;
		std::string Compile()override{
		//编译：提供代码段起点，每条命令按需获取代码，保证迭代器永远指向完整代码的起点
			std::string final_code="@256\nD=A\n@SP\nM=D\n";//初始化
			iter_=file_.begin();
			while(iter_!=file_.end()){
				if(*iter_=="push"){
					final_code+=PushCommand(iter_).Compile();
				}else if(*iter_=="pop"){
					final_code+=PopCommand(iter_).Compile();
				}
				final_code+="\n\n";//每编译完一句完整的语句，添加分割
			}
			final_code+="(END)\n  @END\n0;JMP";
			return final_code;
		}
	private:
		std::list<std::string>::iterator iter_;
	};
}
#endif