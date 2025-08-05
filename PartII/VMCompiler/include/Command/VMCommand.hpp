#ifndef VMCOMMAND_HPP
#define VMCOMMAND_HPP

#include <string>
#include <vector>
#include <list>
namespace VM{
	class VMCommand{
	//VM代码
	public:
		VMCommand(std::list<std::string>::iterator& iter){
			pieces_.push_back(*iter);//每条VM代码的第一段
			iter++;//获取完本段代码后，迭代器向后移动
		}
		virtual ~VMCommand()=default;
		virtual std::string Compile()const=0;//编译方法
		static void SetCurrentFileName(const std::string& name){
			current_file_name_="F"+name;//这里给文件名加了一个F
		}
	protected:
		std::vector<std::string> pieces_;
		static std::string current_file_name_,current_function_name_;
	};
}

#endif