#include "Command/FunctionCommand.hpp"
#include "Command/MemoryCommand.hpp"
#include <list>
#include <string>
using namespace VM;
using std::string;

string FunctionClaimCommand::Compile()const{
    string hack_code;
    hack_code+="("+name_+")\n";//声明标签
    std::list<string> push_constant_0={"push","constant","0"};//复用push
    for(int i=0;i<std::stoi(var_num_);i++){
        //在栈中压入变量以作为local段
        auto iter=push_constant_0.begin();
        hack_code+=PushCommand(iter).Compile();
    }
    return hack_code;
}

string CallCommand::Compile()const{
    string hack_code,push_D;
    push_D="@SP\nM=M+1\nA=M-1\nM=D\n";//将D放入栈顶
    hack_code+="@"+return_label_+"\nD=A\n";
    hack_code+=push_D;//将返回点地址放入栈顶
    hack_code+="@LCL\nD=M\n";
    hack_code+=push_D;//将LCL放在栈顶
    hack_code+="@ARG\nD=M\n";
    hack_code+=push_D;//将ARG放在栈顶
    hack_code+="@THIS\nD=M\n";
    hack_code+=push_D;//将THIS放在栈顶
    hack_code+="@THAT\nD=M\n";
    hack_code+=push_D;//将THAT放在栈顶
    int offset=std::stoi(var_num_)+5;//ARG对SP的负偏移量的绝对值
    hack_code+="@"+std::to_string(offset)+"\nD=A\n";
    hack_code+="@SP\nD=M-D\n@ARG\nM=D\n";//设置被调用函数的ARG
    hack_code+="@SP\nD=M\n@LCL\nM=D\n";//设置被调用函数的LCL
    hack_code+="@"+name_+"\n0;JMP\n";//前往目标函数
    hack_code+="("+return_label_+")\n";//添加返回点
    return hack_code;
}
string ReturnCommand::Compile()const{
	string hack_code,pop_to_D,loop_get_context;
	//操作:将栈顶元素弹出到D
	pop_to_D="@SP\nAM=M-1\nD=M\n";
	//操作:获取*(endFrame-1)的值到D,并将endFrame迭代-1
	loop_get_context="@endFrame\nAM=M-1\nD=M\n";

	hack_code+="@LCL\nD=M\n@endFrame\nM=D\n";//将调用者上下文的结尾保存到endFrame
	hack_code+="@5\nA=D-A\nD=M\n@retAddr\nM=D\n";//得到*(endFrame-5)并存入retAddr
	hack_code+=pop_to_D;
	hack_code+="@ARG\nA=M\nM=D\n";//设置第一个参数为返回值
	hack_code+="@ARG\nD=M\n@SP\nM=D+1\n";//将栈顶指针设置为ARG+1
	//恢复调用者上下文,顺序与存储顺序相反
	hack_code+=loop_get_context;
	hack_code+="@THAT\nM=D\n";
	hack_code+=loop_get_context;
	hack_code+="@THIS\nM=D\n";
	hack_code+=loop_get_context;
	hack_code+="@ARG\nM=D\n";
	hack_code+=loop_get_context;
	hack_code+="@LCL\nM=D\n";
	//恢复完毕,返回调用点
	hack_code+="@retAddr\nA=M\n0;JMP\n";
	return hack_code;
}