#include "replace.hpp"

int getFileIn(std::string filename, std::ifstream &fileIn) {
	fileIn.open(filename.c_str());
	if (!fileIn) {
		std::cout << "Cannot open file" << std::endl;
		return (1);
	}
	return (0);
}

int getFileOut(std::string filename, std::ofstream &fileOut) {
	fileOut.open((filename + ".replace").c_str());
	if (!fileOut) {
		std::cout << "Cannot open file" << std::endl;
		return (1);
	}
	return (0);
}

int replace(std::ifstream &fileIn, std::ofstream &fileOut, std::string s1, std::string s2) {
	int 		n_occ = 0;
	std::string line;
	while (std::getline(fileIn, line)) {
		std::size_t pos = 0;
		while ((pos = line.find(s1, pos)) != std::string::npos) {
			n_occ++;
			line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
			pos += s2.length();
		}
		fileOut << line << std::endl;
	}
	return (n_occ);
}

int correctInput(int ac, char **av) {
	if (ac != 4) {
		std::cout << "Wrong args, please use like this : ./replace filename s1 s2" << std::endl;
		return (1);
	}
	std::string file = av[1];
	std::string s1 = av[2];
	if (!file.length()) {
		std::cout << "Filename cannot be empty" << std::endl;
		return (1);
	}
	if (!s1.length()) {
		std::cout << "S1 cannot be empty" << std::endl;
		return (1);
	}
	return (0);
}

int main(int ac, char **av) {
	if (correctInput(ac, av))
		return (1);
	std::ifstream fileIn;
	if (getFileIn(av[1], fileIn))
		return (1);
	
	std::ofstream fileOut;
	if (getFileOut(av[1], fileOut))
		return (1);
	
	int n_occ = replace(fileIn, fileOut, av[2], av[3]);
	std::cout << "number of occurrences found : " << n_occ << std::endl;

	fileIn.close();
	fileOut.close();
	
	return (0);
}