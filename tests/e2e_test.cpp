
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

int main(int argc, char** argv) {

	if (argc != 3) return 2;
	char* message = (char*) calloc (sizeof(char), 512);
	strcat(message, "./ParaCL ");
	strcat(message, argv[1]);
	strcat(message, " ");
	strcat(message, argv[2]);
	strcat(message, " > tmp_answer.txt");

	system(message);

	int res;
    std::ifstream ret{"ret.txt"};
    ret >> res;

    std::cout << "res is " << res << std::endl;

    if (res != 0) abort();
	return res;
}
