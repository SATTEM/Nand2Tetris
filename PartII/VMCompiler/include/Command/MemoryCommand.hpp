#ifndef MEMORYCOMMAND_HPP
#define MEMORYCOMMAND_HPP
#include "VMCommand.hpp"
namespace VM {
	class MemoryCommand:public VMCommand{
	//内存操作基类
	public:
		MemoryCommand(std::list<std::string>::iterator& iter):VMCommand(iter){
			pieces_.push_back(*iter);//内存操作三段代码中的第二段(内存类型)
			iter++;
			pieces_.push_back(*iter);//第三段(内存位置)
			iter++;
		}
		virtual ~MemoryCommand()=default;
	};
	class PushCommand:public MemoryCommand{
	public:
		PushCommand(std::list<std::string>::iterator& iter):MemoryCommand(iter){}
		virtual ~PushCommand()=default;
		std::string Compile()const override;
	};
	class PopCommand:public MemoryCommand{
	public:
		PopCommand(std::list<std::string>::iterator& iter):MemoryCommand(iter){}
		virtual ~PopCommand()=default;
		std::string Compile()const override;
	};
}

#endif