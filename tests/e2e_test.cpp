
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>

int main(int argc, char** argv) {

	if (argc != 3) return 2;
	char* message = (char*) calloc (sizeof(char), 512);
	strcat(message, "./ParaCL ");
	strcat(message, argv[1]);
	strcat(message, " ");
	strcat(message, argv[2]);
	strcat(message, " > tmp_answer.txt");
	/*
	std::string message("./ParaCL ");
	message += argv[1];
	message += " ";
	message += argv[2];
	message += " > tmp_answer";
	strcpy(message, message);*/
//"./ParaCL %s %s > tmp_answer", argv[1], argv[2]
	int result = system(message);
	printf("%d\n", result);
std::cout << std::endl << std::endl << result << std::endl;
	//remove("tmp_answer");

	return result;
}
