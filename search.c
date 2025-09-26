#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device.h"
#include "search.h"

// 특정 센서 검색하는 함수
void search(const char *binfile, const char *keyword) {
    FILE *fp = fopen(binfile, "rb"); // binary 파일을 읽기 모드로 연결
    if (!fp) { // 파일이 열리지 않을 경우
        perror("파일 열기 실패");
        return;
    }

    Sensor s; // 파일에서 읽은 데이터를 저장할 구조체 변수
    int find = 0; // 키워드 찾으면 1, 못 찾으면 0

    while (fread(&s, sizeof(Sensor), 1, fp) == 1) { // sensor구조체만큼 읽어서 변수 s에 저장						    
        if (strstr(s.name, keyword) != NULL) {  // 특정 센서 정보가 같다면
            find = 1;  // 찾았다는 표시를 해줌.
            printf("해당 센서의 정보 :  ID=%d, Name=%s, Status=%s\n",
                   s.id, s.name, s.status);
        }
    }

    if (!find) {   // while문이 끝난 후에도 찾은 게 없다면 해당 문장 출력.
        printf("'%s'에 해당되는 값이 존재하지 않습니다.\n", keyword);
    }

    fclose(fp);
}

