#include <ios>
#include <iostream>
#include <fstream>
#include "HackFile.hpp"
int main(int argc,char* argv[]){
	if(argc!=2){std::cerr<<"Compiler needs ONE input file!"<<std::endl;return -1;}
	std::string input(argv[1]);
	if(input.find(".asm")==input.npos){
		std::cerr<<"Input is not a .asm file!"<<std::endl;
		return -1;
	}
	std::fstream fs(argv[1],std::ios_base::in);
	if(!fs){std::cerr<<"Failed to open "<<argv[1];return -1;}
	HackFile file(fs);
	fs.close();
	std::string output=input.substr(0,input.find('.'))+".hack";
	fs.open(output,std::ios_base::out);
	fs<<file;
	fs.close();
}