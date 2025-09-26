#include <stdio.h>
#include <stdlib.h>
#include "device.h"
#include "init.h"

void init(const char *input, const char *output) {    // 텍스트 파일을 binary 파일로 저장하기.
    FILE *fin = fopen(input, "r");   // 텍스트 파일을 읽기 모드로 열기
    FILE *fout = fopen(output, "wb");   // binary 파일 열기

    if (!fin || !fout) {   // 둘 중 하나라도 없다면 출력 파일 열기 실패
        perror("파일 열기 실패");
        return;
    }

    Sensor s;
    while (fscanf(fin, "%d %s %s", &s.id, s.name, s.status) == 3) { // 조건에 맞는 텍스트 파일에서 한 줄씩 읽어 Sensor 구조체에 저장 후 binary 파일에 저장하기.
        fwrite(&s, sizeof(Sensor), 1, fout);
    }

    fclose(fin);
    fclose(fout);
}

