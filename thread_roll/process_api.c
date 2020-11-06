#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int rc = fork();

    if (rc == 0) {
        printf("Child process\n");
    }
    else if (rc > 0) {
        printf("Parent successfully forked, child process id: %d\n", rc);
    }
    else {
        printf("Fork failed, errno: %d\n", errno);
    }
}
