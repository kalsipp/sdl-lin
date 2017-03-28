#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
std::string encrypt(const std::string & text){
	char key = 'p';
	std::string output = text;
	for(int i = 0; i < text.size(); ++i){
		output[i] = text[i]^key;
	}
	return output;
}
int main(int argc, char* argv[]){
	if(argc == 1){
		std::cerr << "Please enter input parameters in the form 'name.txt'." << std::endl;
		return -1;
	}
	for (int i = 1; i < argc; ++i){
		std::cout << i << std::endl;
		std::string filename = argv[i];
		std::string ending = filename.substr(filename.size()-4, filename.size());
		std::string output_name = "";
		if(ending == ".txt"){
			 output_name = filename.substr(0, filename.size()-4) + ".scr";
		}else if(ending == ".scr"){
			 output_name = filename.substr(0, filename.size()-4) + ".usc";
		}else{
			std::cout << "Filename " << filename << " of wrong ending. use .txt to encrypt or .scr do decrypt" << std::endl;
		}
		std::cout << "Encrypting " << filename << std::endl;
		//std::string name = filename.substr(0, filename.find('.'));
		std::ifstream infile(filename.c_str());
		std::string data;
		std::stringstream buffer;
		buffer << infile.rdbuf();
		infile.close();
		data = buffer.str();
		std::string output = encrypt(data);



		std::cout << "Writing output to " << output_name << std::endl;

		std::ofstream output_file;
		output_file.open(output_name.c_str());
		output_file << output;
		output_file.close();
	}
}