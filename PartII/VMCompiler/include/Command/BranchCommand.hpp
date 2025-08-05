#ifndef BRANCHCOMMAND_HPP
#define BRANCHCOMMAND_HPP
#include "VMCommand.hpp"
#include <list>
#include <string>
namespace VM {
	class BranchCommand:public VMCommand{
	public:
		BranchCommand(std::list<std::string>::iterator& iter):VMCommand(iter){
			label_=current_function_name_+"$"+*iter;//需要一个参数，即标签名
			iter++;
		}
		virtual ~BranchCommand()=default;
	protected:
		std::string label_;	
	};
	class LabelCommand:public BranchCommand{
	public:
		LabelCommand(std::list<std::string>::iterator& iter):BranchCommand(iter){}
		~LabelCommand()=default;
		std::string Compile()const override;
	};
	class GotoCommand:public BranchCommand{
	public:
		GotoCommand(std::list<std::string>::iterator& iter):BranchCommand(iter){}
		~GotoCommand()=default;
		std::string Compile()const override;
	};
	class IfGotoCommand:public BranchCommand{
	public:
		IfGotoCommand(std::list<std::string>::iterator& iter):BranchCommand(iter){}
		~IfGotoCommand()=default;
		std::string Compile()const override;
	};
}

#endif