#ifndef FUNCTIONCOMMAND_HPP
#define FUNCTIONCOMMAND_HPP
#include "VMCommand.hpp"
#include <list>
#include <string>
namespace VM {
	class FunctionClaimCommand:public VMCommand{
	public:
		FunctionClaimCommand(std::list<std::string>::iterator& iter):VMCommand(iter){
			current_function_name_=*iter;//取得函数名称
			name_=current_function_name_;
			iter++;
			var_num_=*iter;//局部变量的数量
			iter++;
		}
		~FunctionClaimCommand()=default;
		std::string Compile()const override;
	private:
		std::string name_,var_num_;
	};
	class CallCommand:public VMCommand{
	public:
		CallCommand(std::list<std::string>::iterator& iter):VMCommand(iter){
			current_function_name_=*iter;//取得函数名称
			name_=current_function_name_;
			iter++;
			var_num_=*iter;//取得传递参数的数量
			iter++;
			static int global_call_count=0;
			global_call_count++;
			return_label_=current_file_name_+"$ret."+std::to_string(global_call_count);
		}
		~CallCommand()=default;
		std::string Compile()const override;
	private:
		std::string name_,var_num_,return_label_;
		static int call_nums_;
	};
	class ReturnCommand:public VMCommand{
	public:
		ReturnCommand(std::list<std::string>::iterator& iter):VMCommand(iter){}//不需要参数
		~ReturnCommand()=default;
		std::string Compile()const override;
	};
}

#endif