#include "Command/VMCommand.hpp"
#include "Command/MemoryCommand.hpp"
#include <string>
#include <unordered_map>

std::unordered_map<std::string,std::string> seg_map={
	{"local","LCL"},{"argument","ARG"},{"static","static"},
	{"this","THIS"},{"that","THAT"},{"pointer","pointer"},
	{"constant","constant"},{"tmp","tmp"}};//映射

std::string VM::PushCommand::Compile()const{
	std::string hack_code;
	std::string put_M_in_SP="D=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
	std::string seg=seg_map[pieces_[1]];
	if(seg=="LCL"||seg=="ARG"||seg=="THIS"||seg=="THAT"){
		std::string access_point_addr="@"+pieces_[2]+"\nD=A\n@"+seg+"\nA=D+M\n";//访问指向的地址
		hack_code+=access_point_addr;
		hack_code+=put_M_in_SP;
	}else if(seg=="constant"){
		hack_code+="@"+pieces_[2]+"\n";
		hack_code+="D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
	}else if(seg=="static"){
		//注意：这里和课程标准不同，手动添加了一个F以避免文件名以数字开头的情况
		hack_code+="@F"+current_file_name_+"."+pieces_[2]+"\n";
		hack_code+=put_M_in_SP;
	}else if(seg=="tmp"){
		int temp_address=5+std::stoi(pieces_[2]);
		seg=std::to_string(temp_address);
		hack_code+="@"+seg+"\n";
		hack_code+=put_M_in_SP;
	}else if(seg=="pointer"){
		std::string target;
		if(pieces_[2]=="0"){
			target="THIS";
		}else{
			target="THAT";
		}
		hack_code+="@"+target+"\n";
		hack_code+=put_M_in_SP;
	}
	return hack_code;
}
std::string VM::PopCommand::Compile()const{
	std::string hack_code;
	std::string pop_to_D="@SP\nM=M-1\nA=M\nD=M\n";
	std::string seg=seg_map[pieces_[1]];
	if(seg=="LCL"||seg=="ARG"||seg=="THIS"||seg=="THAT"){
		std::string store_point_addr="@"+pieces_[2]+"\nD=A\n";
		store_point_addr+="@"+seg+"\nD=D+M\n@addr\nM=D\n";//存储目标地址到addr
		std::string fetch_D_to_M="@addr\nA=M\nM=D\n";//将D存入目标
		hack_code+=store_point_addr;
		hack_code+=pop_to_D;
		hack_code+=fetch_D_to_M;
	}else if(seg=="tmp"){
		int temp_address=5+std::stoi(pieces_[2]);
		seg=std::to_string(temp_address);
		hack_code+=pop_to_D;
		hack_code+="@"+seg+"\nM=D\n";//将D存入目标
	}else if(seg=="static"){
		hack_code+=pop_to_D;
		//注意：这里和课程标准不同，手动添加了一个F以避免文件名以数字开头的情况
		hack_code+="@F"+current_file_name_+"."+pieces_[2]+"\nM=D\n";
	}else if(seg=="pointer"){
		std::string target;
		if(pieces_[2]=="0"){
			target="THIS";
		}else{
			target="THAT";
		}
		hack_code+=pop_to_D;
		hack_code+="@"+target+"\nM=D\n";
	}
	return hack_code;
}