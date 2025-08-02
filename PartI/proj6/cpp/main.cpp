#include <ios>
#include <iostream>
#include <fstream>
#include "HackFile.hpp"
int main(int argc,char* argv[]){
	if(argc==1){std::cerr<<"No input";return -1;}
	if(argc==2){std::cerr<<"Lack of input or output parameter";return -1;}
	if(argc>3){std::cerr<<"Too many parameters";return -1;}
	std::fstream fs(argv[1],std::ios_base::in);
	if(!fs){std::cerr<<"Failed to open "<<argv[1];return -1;}
	HackFile file(fs);
	fs.close();
	fs.open(argv[2],std::ios_base::out);
	fs<<file;
	fs.close();
}