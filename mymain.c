#include "new_shell.h"

/**
 * The main entry point of the program.
 *
 * @param ac The argument count.
 * @param av The argument vector.
 * @return   0 on success, 1 on error.
 */
int main(int ac, char **av)
{
    new_info_t info[] = {NEW_INFO_INIT};
    int fd = 2;

    /* Perform some assembly magic */
    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                new_eputs(av[0]);
                new_eputs(": 0: Can't open ");
                new_eputs(av[1]);
                new_eputchar('\n');
                new_eputchar(NEW_BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fd;
    }

    populate_new_env_list(info);
    read_new_history(info);
    new_hsh(info, av);
    return (EXIT_SUCCESS);
}
