#ifndef FACTORY_HPP
#define FACTORY_HPP
#include "VMCommand.hpp"
#include <memory>
#include <string>
namespace VM{
	class CommandFactory{
	//命令工厂
	public:
		CommandFactory()=default;
		virtual ~CommandFactory()=default;
		virtual std::unique_ptr<VMCommand> Produce(std::list<std::string>::iterator& iter)=0;//创建接口
	};
	template<typename T>
	class ConcreteFactory:public CommandFactory{
	public:
		std::unique_ptr<VMCommand> Produce(std::list<std::string>::iterator& iter){
			return std::make_unique<T>(iter);//返回命令实例
		}
	};
};

#endif