#include <stdio.h>
#include <unistd.h>


int main(int ac, char *av[], char *env[])
{
    char *ptr[] = {"/bin/echo", "/Users/plertsir", NULL};

    execve(*ptr, ptr, NULL);
}