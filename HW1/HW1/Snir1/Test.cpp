#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "Main.cpp"
#include "dirent.h"

int main()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("c:\\src\\")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
			Main::main
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return EXIT_FAILURE;
	}
}
