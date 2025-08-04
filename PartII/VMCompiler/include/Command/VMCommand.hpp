#ifndef VMCOMMAND_HPP
#define VMCOMMAND_HPP

#include <string>
#include <vector>
#include <list>
namespace VM{
	enum class CommandType{Push,Pop,Add,Sub,And,Or,Not,Neg,Eq,Gt,Lt};
	class VMCommand{
	//VM代码
	public:
		VMCommand(std::list<std::string>::iterator& iter){
			pieces_.push_back(*iter);//每条VM代码的第一段
			iter++;//获取完本段代码后，迭代器向后移动
		}
		virtual ~VMCommand()=default;
		virtual std::string Compile()const=0;//编译方法
		const CommandType& GetType()const{return type_;}
	protected:
		CommandType type_;
		std::vector<std::string> pieces_;
	};
}

#endif