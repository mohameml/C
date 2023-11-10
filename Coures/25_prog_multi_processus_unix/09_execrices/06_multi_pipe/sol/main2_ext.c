#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#define n 10

int main(void)
{
    int fd[n][2];
    int pid_list[n];

    for (int i = 0; i < n; i++)
    {
        if (pipe(fd[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }

    for (int i = 1; i < n; i++)
    {
        int pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0)
        {
            for (int j = 0; j < n; j++)
            {
                if (j != i - 1 && j != i)
                {
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }

            int x;

            if (i == 1)
            {
                x = 0;
            }
            else
            {
                read(fd[i - 1][0], &x, sizeof(int));
                close(fd[i - 1][0]);
            }

            x += 1;
            write(fd[i][1], &x, sizeof(int));
            close(fd[i][1]);
            exit(0);
        }
        else
        {
            pid_list[i] = pid;
        }
    }

    for (int j = 0; j < n; j++)
    {
        if (j != 0 && j != n - 1)
        {
            close(fd[j][0]);
            close(fd[j][1]);
        }
    }

    int x = 0;
    write(fd[1][1], &x, sizeof(int));
    close(fd[1][1]);

    for (int i = 1; i < n; i++)
    {
        waitpid(pid_list[i], NULL, 0);
    }

    read(fd[n - 1][0], &x, sizeof(int));
    close(fd[n - 1][0]);

    printf("La valeur de x après le tour est : %d\n", x);

    return 0;
}