#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // read, wirte, lseek 사용하면 해당 헤더파일 추가
#include <fcntl.h>     // open, O_RDWR 사용하면 해당 헤더파일 추가
#include "device.h"   // Sensor 구조체 사용
#include "update.h"   // update 함수 원형 선언

// 기능: 특정 ID의 센서를 찾아서 상태(status)를 수정
void update (int fd, int id) {
	Sensor s;
	int found = 0;

	lseek(fd, 0, SEEK_SET); // 처음부터 탐색하도록 지정.

	while (read(fd, &s, sizeof(Sensor)) == sizeof(Sensor)) {   // 파일을 읽어서
   		if (s.id == id) {  // 조건이 맞으면
       			found = 1;
       		 	printf(수정 전 데이터 출력 : ID=%d, Name=%s, Status=%s\n", s.id, s.name, s.status);

        		printf("수정 후 데이터 입력: ");
        		scanf("%s", s.status); // 상태만 재입력

        		// 파일 포인터를 한 레코드 뒤로 이동시켜야 수정된 값으로 덮어쓰기 가능
        		lseek(fd, -((off_t)sizeof(Sensor)), SEEK_CUR);

        		// 수정된 값 덮어쓰기
        		write(fd, &s, sizeof(Sensor));

        		printf("ID %d 수정 완료했습니다.료.\n", id);
        		break;
    		}
	}

	if (!found){
    		printf("ID %d 센서가 존재하지 않습니다..\n", id);
	}
}



