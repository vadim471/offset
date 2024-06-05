#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int fillArrayByNumbers(){
    int file = open("../file.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if (file == - 1){
        return 1;
    }
    void *map;
    int array[] = {16, 28, 44, 0,
                   1, 2, 0,
                   3, 4, 99, 0,
                   5, 32, 1, 0};
    lseek(file, sizeof(array) - 1, SEEK_SET);
    if (write(file, "", 1) == -1) {
        return 2;
    }
    map = mmap(0, sizeof(array), PROT_WRITE, MAP_SHARED, file, 0);
    if (map == MAP_FAILED) {
        return 3;
    }
    close(file);
    memcpy(map, array, sizeof(array));
    msync(map, sizeof(array), MS_SYNC);
    munmap(map, sizeof(array));
}

void printArrayByNumber(int array_number) {
    struct stat s;
    int *map;
    int file = open("../file.bin", O_RDONLY, 0);

    fstat(file, &s);
    map = (int*) mmap(0, s.st_size, PROT_READ, MAP_SHARED, file, 0);

    close(file);

    int i = map[array_number] / sizeof(int);
    while (map[i] != 0) {
        printf("%d ", map[i]);
        i++;
    }
}

int main() {
    fillArrayByNumbers();

    int array_number;
    scanf("%d", &array_number);
    printArrayByNumber(array_number - 1);
    return 0;
}
