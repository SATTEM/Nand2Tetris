#ifndef HACKFILE_HPP
#define HACKFILE_HPP
#include <cctype>
#include <list>
#include <string>
#include <fstream>
#include <unordered_map>
#include "CommonFile.hpp"
#include "Instruction.hpp"

namespace{
	std::unordered_map<std::string, int> predefine_table = {
		{"R0", 0},   {"R1", 1},   {"R2", 2},   {"R3", 3},
		{"R4", 4},   {"R5", 5},   {"R6", 6},   {"R7", 7},
		{"R8", 8},   {"R9", 9},   {"R10", 10}, {"R11", 11},
		{"R12", 12}, {"R13", 13}, {"R14", 14}, {"R15", 15},
		{"SCREEN", 16384},{"KBD", 24576},{"SP", 0},{"LCL", 1},
		{"ARG", 2},{"THIS", 3},{"THAT", 4}
	};
}
class HackFile:public CommonFile{
//Hack语言文件
public:
	HackFile(std::fstream& fs):CommonFile(fs){
		SplitCode();
	}
	virtual ~HackFile()=default;
private:
	void SplitCode(){
		//分割同一行内的代码
		std::list<std::string> tmp;
		for(auto& line:file_){
			auto blank_pos=line.find_first_of(' ');
			for(size_t i=0;i!=line.npos;i=blank_pos){
				tmp.push_back(line.substr(i,blank_pos-i));
				blank_pos=line.find(' ',blank_pos+1);
			}
		}
		file_=tmp;
	}
	void FirstPass(){
		//第一轮处理：解决标签
		table_.merge(predefine_table);//载入预定义符号
		auto iter=file_.begin();
		int row_index=0;
		while(iter!=file_.end()){
			//先登记标签
			if((*iter)[0]=='('){
				//找到一个标签声明
				std::string label=iter->substr(1,iter->length()-2);//得到括号内部分
				table_[label]=row_index;
				iter=file_.erase(iter);
			}else{
				//找到一条指令
				row_index++;
				iter++;
			}
		}
		iter=file_.begin();
		while(iter!=file_.end()){
			//再替换标签
			if((*iter)[0]=='@'){
				std::string address=iter->substr(1);//得到A指令涉及的地址
				if(table_.find(address)!=table_.end()){
					//是已知的标签
					*iter="@"+std::to_string(table_[address]);//将标签替换为数字
				}
			}
			iter++;
		}
	}
	void SecondPass(){
		//第二轮处理：解决变量
		int var_index=16;//变量的位置从RAM[16]开始
		for(auto iter=file_.begin();iter!=file_.end();iter++){
			if((*iter)[0]=='@'&&std::isdigit((*iter)[1])==false){
				//找到地址以非数字开头(变量不允许以数字开头)的A指令
				std::string var=iter->substr(1);
				if(table_.find(var)==table_.end()){
					//首次遇见此变量
					table_[var]=var_index++;
				}
				*iter="@"+std::to_string(table_[var]);//替换地址
			}
		}
	}
	void Compile()override{
		FirstPass();
		SecondPass();
		//真正进行编译
		for(auto& item:file_){
			if(item.find('@')!=item.npos){
				item=AInstruction(item).Compile();//为A指令
			}else{
				item=CInstruction(item).Compile();//为C指令
			}
		}
	}
private:
	std::unordered_map<std::string,int> table_;//符号表
};
#endif