/*
 * File name: single_thread_copy.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>

#define FILE_READ_SECTOR 128

int main(int argc, char *argv[])
{
    uint8_t buf[FILE_READ_SECTOR] = {0};

    if (argc != 3) {
        printf("invalid parameters\n");
        return -1;
    }

    int fd_in, fd_out;
    int read_num;

    /* time_t start_t, end_t; */
    /* time(&start_t); */
    clock_t t;

    t = clock(); 

    fd_in = open(argv[1], O_RDONLY);
    fd_out = open(argv[2],  O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd_in < 0) {
        printf("input file is not exist\n");
        return -1;
    }

    while (1) {
        read_num = read(fd_in, buf, FILE_READ_SECTOR);

        if (read_num == 0)
            break;

        write(fd_out, buf, read_num);
    }

    close(fd_in);
    close(fd_out);

    /* sleep(5); */
    /* time(&end_t); */
    /* printf("using time: %f\n", difftime(end_t, start_t)); */

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("took %f seconds to execute \n", time_taken);


    return 0;
}

