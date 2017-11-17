#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "dirent.h"
#include <iostream>

int main()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("c:\\src\\")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
			char cmd[1024];
			sprintf(cmd, ".\Debug\Snir1.exe %s", ent->d_name);
			std::cout << cmd;
			system(cmd);
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return EXIT_FAILURE;
	}
}
