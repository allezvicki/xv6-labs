#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(2, "Usage: sleep <time>\n");
		exit(1);
	}
	int sleep_dur = atoi(argv[1]);
	if (sleep(sleep_dur) != 0) {
		fprintf(2, "sleep: error\n");
		exit(1);
	}
	exit(0);
}
