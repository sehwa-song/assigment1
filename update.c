#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device.h"   // Sensor 구조체 사용
#include "update.h"   // update 함수 원형 선언

// 기능: 특정 ID의 센서를 찾아서 상태(status)를 수정
void update(const char *binfile, int id) {
    FILE *fp = fopen(binfile, "r+b"); // 읽rl, 쓰기 모드
    if (!fp) {
        perror("파일 열기 실패"); // 파일이 없다면 열기 실패
        return;
    }

    Sensor s;
    int found = 0;

   
    while (fread(&s, sizeof(Sensor), 1, fp) == 1) {  // binary 파일에서 구조체 단위로 읽기
        if (s.id == id) {   // sensor의 id와 해당 id가 같다면 특정 id 찾음.
            found = 1;

            printf("기존 데이터: ID=%d, Name=%s, Status=%s\n",
                   s.id, s.name, s.status);

            printf("새로운 상태 입력: ");
            scanf("%9s", s.status);

            fseek(fp, -((long)sizeof(Sensor)), SEEK_CUR);  // 해당 자리에 데이터를 덮어 써야 돼서 하나의 구조체 크기만큼 뒤로 이동하기

            fwrite(&s, sizeof(Sensor), 1, fp);   // 수정된 데이터를 덮어 쓰기

            printf("ID %d  수정 완료.\n", id);
            break;
        }
    }

    if (!found) {  // 만약 찾지 못했을 경우, 해당 문장 출력
        printf("ID %d 레코드를 찾을 수 없습니다.\n", id);
    }

    fclose(fp);
}

