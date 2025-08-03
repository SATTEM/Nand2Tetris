#ifndef COMMONFILE_HPP
#define COMMONFILE_HPP

#include <fstream>
#include <list>
#include <string>
namespace {
	void OrganizeLine(std::string& line){
		//整理一行，只留下代码本身，每一段代码后有一个空格
		auto it=line.begin();
		while(it!=line.end()){
			if(*it=='/'){
				//出现斜杠，则后面都是注释
				it=line.erase(it,line.end());
				break;
			}
			if(std::isblank(*it)){
				if(it==line.begin()||it+1==line.end()){
					it=line.erase(it);//删除行首行尾空白
				}else if(std::isblank(*(it+1))||*(it+1)=='/'){
					it=line.erase(it);//删除连续空白或注释前空白
				}else{
					it++;//保留代码之间的一格空格
				}
			}else{
				it++;
			}
		}
		if(line.empty()==false){
			line.push_back(' ');//若至少有一段代码，添加行尾空格
		}
	}
}
class CommonFile{
//代码文件
public:
	CommonFile(std::fstream& fs){
		//读取文件并提取代码
		std::string line;
		while(std::getline(fs,line)){
			OrganizeLine(line);
			if(line.empty()){continue;}//跳过空行
			auto blank_pos=line.find_first_of(' ');
			for(size_t i=0;i!=line.npos;i=blank_pos){
				file_.push_back(line.substr(i,blank_pos-i));
				blank_pos=line.find(' ',blank_pos+1);
			}//添加代码
		}
	}
	virtual ~CommonFile()=default;
	virtual void Compile()=0;//具体的编译行为
	friend std::fstream& operator<<(std::fstream& fs,CommonFile& file);//对文件进行编译并输出
protected:
	std::list<std::string> file_;
};

inline std::fstream& operator<<(std::fstream& fs,CommonFile& file){
		file.Compile();
		for(const auto& item:file.file_){
			fs<<item<<std::endl;
		}
		return fs;
	}
#endif