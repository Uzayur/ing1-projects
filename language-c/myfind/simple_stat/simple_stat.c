#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        struct stat stats;
        if (stat(argv[i], &stats) == 0)
        {
            printf("st_dev=%ld\n", stats.st_dev);
            printf("st_ino=%ld\n", stats.st_ino);
            printf("st_mode=%d\n", stats.st_mode);
            printf("st_nlink=%ld\n", stats.st_nlink);
            printf("st_uid=%d\n", stats.st_uid);
            printf("st_gid=%d\n", stats.st_gid);
            printf("st_rdev=%ld\n", stats.st_rdev);
            printf("st_size=%ld\n", stats.st_size);
            printf("st_atime=%ld\n", stats.st_atime);
            printf("st_mtime=%ld\n", stats.st_mtime);
            printf("st_ctime=%ld\n", stats.st_ctime);
            printf("st_blksize=%ld\n", stats.st_blksize);
            printf("st_blocks=%ld\n", stats.st_blocks);
        }
        else
            return 0;
    }
    return 1;
}
