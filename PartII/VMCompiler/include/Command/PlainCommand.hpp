#ifndef PLAINCOMMAND_HPP
#define PLAINCOMMAND_HPP
#include "VMCommand.hpp"
#include <string>
namespace VM {
	class PlainCommand:public VMCommand{
	//一般命令基类
	public:
		PlainCommand(std::list<std::string>::iterator& iter):VMCommand(iter){
			//一般命令无参数
		}
		virtual ~PlainCommand()=default;
	};
	//各种一般命令的声明
	class NotCommand:public PlainCommand{
	public:
		NotCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~NotCommand()=default;
		std::string Compile()const override;
	};
	class NegCommand:public PlainCommand{
	public:
		NegCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~NegCommand()=default;
		std::string Compile()const override;
	};
	class AddCommand:public PlainCommand{
	public:
		AddCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~AddCommand()=default;
		std::string Compile()const override;
	};
	class SubCommand:public PlainCommand{
	public:
		SubCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~SubCommand()=default;
		std::string Compile()const override;
	};
	class AndCommand:public PlainCommand{
	public:
		AndCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~AndCommand()=default;
		std::string Compile()const override;
	};
	class OrCommand:public PlainCommand{
	public:
		OrCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~OrCommand()=default;
		std::string Compile()const override;
	};
	class EqCommand:public PlainCommand{
	public:
		EqCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~EqCommand()=default;
		std::string Compile()const override;
	};
	class GtCommand:public PlainCommand{
	public:
		GtCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~GtCommand()=default;
		std::string Compile()const override;
	};
	class LtCommand:public PlainCommand{
	public:
		LtCommand(std::list<std::string>::iterator& iter):PlainCommand(iter){}
		virtual ~LtCommand()=default;
		std::string Compile()const override;
	};
}

#endif