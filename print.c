#include <stdio.h>
#include "device.h"

void print_all(FILE *fp) {
    Sensor s;
    fseek(fp, 0, SEEK_SET);  // 맨 처음으로 파일 이동
    while (fread(&s, sizeof(Sensor), 1, fp) == 1) {
        printf("ID= %d, Name= %s, Status= %s\n", s.id, s.name, s.status);
    }
}

