#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <bitset>
#include <cstddef>
#include <string>
#include <unordered_map>
namespace {
    // comp字段
    std::unordered_map<std::string, std::bitset<7>> comp_map = {
        {"0",   std::bitset<7>("0101010")},
        {"1",   std::bitset<7>("0111111")},
        {"-1",  std::bitset<7>("0111010")},
        {"D",   std::bitset<7>("0001100")},
        {"A",   std::bitset<7>("0110000")},
        {"!D",  std::bitset<7>("0001101")},
        {"!A",  std::bitset<7>("0110001")},
        {"-D",  std::bitset<7>("0001111")},
        {"-A",  std::bitset<7>("0110011")},
        {"D+1", std::bitset<7>("0011111")},
        {"A+1", std::bitset<7>("0110111")},
        {"D-1", std::bitset<7>("0001110")},
        {"A-1", std::bitset<7>("0110010")},
        {"D+A", std::bitset<7>("0000010")},
        {"D-A", std::bitset<7>("0010011")},
        {"A-D", std::bitset<7>("0000111")},
        {"D&A", std::bitset<7>("0000000")},
        {"D|A", std::bitset<7>("0010101")},
        // M版本
        {"M",   std::bitset<7>("1110000")},
        {"!M",  std::bitset<7>("1110001")},
        {"-M",  std::bitset<7>("1110011")},
        {"M+1", std::bitset<7>("1110111")},
        {"M-1", std::bitset<7>("1110010")},
        {"D+M", std::bitset<7>("1000010")},
        {"D-M", std::bitset<7>("1010011")},
        {"M-D", std::bitset<7>("1000111")},
        {"D&M", std::bitset<7>("1000000")},
        {"D|M", std::bitset<7>("1010101")}
    };

    // dest字段
    std::unordered_map<std::string, std::bitset<3>> dest_map = {
        {"M",   std::bitset<3>("001")},
        {"D",   std::bitset<3>("010")},
        {"MD",  std::bitset<3>("011")},
        {"A",   std::bitset<3>("100")},
        {"AM",  std::bitset<3>("101")},
        {"AD",  std::bitset<3>("110")},
        {"AMD", std::bitset<3>("111")}
    };

    // jump字段
    std::unordered_map<std::string, std::bitset<3>> jump_map = {
        {"JGT", std::bitset<3>("001")},
        {"JEQ", std::bitset<3>("010")},
        {"JGE", std::bitset<3>("011")},
        {"JLT", std::bitset<3>("100")},
        {"JNE", std::bitset<3>("101")},
        {"JLE", std::bitset<3>("110")},
        {"JMP", std::bitset<3>("111")}
    };
}
class Instruction{
//指令基类
public:
	~Instruction()=default;
	Instruction()=default;
	virtual std::string Compile()const=0;//编译为机器码
};
class AInstruction:public Instruction{
//A指令
public:
	~AInstruction()=default;
	AInstruction(const std::string& ins):Instruction(){
		address_=std::bitset<15>(std::stoi(ins.substr(1)));
	}
	std::string Compile()const override{
		return "0"+address_.to_string();
	}
private:
	std::bitset<15> address_;
};
class CInstruction:public Instruction{
//C指令
public:
	~CInstruction()=default;
	CInstruction(const std::string& ins):Instruction(){
		auto dest_pos=ins.find('=');//等号位置
		auto jump_pos=ins.find(';');//分号位置
		if(dest_pos!=ins.npos){
			dest_=dest_map[ins.substr(0,dest_pos)];//有dest部分，查表
		}else{
			dest_=std::bitset<3>("000");
		}
		if(jump_pos!=ins.npos){
			jump_=jump_map[ins.substr(jump_pos+1)];//有jump部分，查表
		}else{
			jump_=std::bitset<3>("000");
		}
		size_t comp_start=(dest_pos!=ins.npos)?dest_pos+1:0;//计算comp起点
		size_t comp_len=(jump_pos!=ins.npos)?jump_pos:ins.length()-comp_start;//计算comp长度
		comp_=comp_map[ins.substr(comp_start,comp_len)];
	}
	std::string Compile()const override{
		return "111"+comp_.to_string()+dest_.to_string()+jump_.to_string();
	}
private:
	std::bitset<3> dest_,jump_;
	std::bitset<7> comp_;
};

#endif