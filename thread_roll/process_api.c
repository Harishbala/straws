#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int rc = fork();

    if (rc == 0) {
        printf("Child process\n");
	int exec_ret = execl("/bin/ls", NULL);
	printf("Exec ret: %d errno: %d\n", exec_ret, errno);
    }
    else if (rc > 0) {
	int wstatus = 0;
	int c_pid = wait(&wstatus);
	printf("Parent successfully forked, child process id: %d\n", rc);

    }
    else {
        printf("Fork failed, errno: %d\n", errno);
    }
}
