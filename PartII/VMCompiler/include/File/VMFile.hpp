#ifndef VMFILE_CPP
#define VMFILE_CPP
#include "Command/Factory.hpp"
#include "CommonFile.hpp"
#include <memory>
#include <string>
#include <unordered_map>
namespace VM{
	class VMFile:public CommonFile{
	//VM代码文件
	public:
		virtual ~VMFile()=default;
		VMFile(std::fstream& fs);
		std::string Compile()override;
		void RegisterCommand(const std::string& cmd,std::unique_ptr<CommandFactory> f){factories_[cmd]=std::move(f);}
	private:
		std::list<std::string>::iterator iter_;
		std::unordered_map<std::string, std::unique_ptr<CommandFactory>> factories_;
	};
}
#endif