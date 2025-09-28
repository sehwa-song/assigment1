#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "device.h"
#include "print.h"
#include "init.h"
#include "update.h"
#include "search.h"

int is_cmd(const char *input, const char *cmd) {  // 명령어 비교 함수
    return strcmp(input, cmd) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) { // 필요한 정보가 3개 미만시 명령어 없음. (정보 부족)
        fprintf(stderr, "%s 실행 방법: 명령어, 파일명\n", argv[0]);
        fprintf(stderr, "가능한 명령어-> init, print, update, search\n");
        return 1;
    }

    if (is_cmd(argv[1], "init")) { // 명령어가 init인 경우 
        if (argc != 4) {  // txt 파일, dinary 파일, 2개의 인자가 필요함
            fprintf(stderr, "사용법: %s init [data.txt] [data_binary.dat]\n", argv[0]);
            return 1;
        }
        init(argv[2], argv[3]); // 조건 만족시, binary 파일로 저장
    } else if (is_cmd(argv[1], "print")) {  // 명령어가 print인 경우
        if (argc != 3) { // binary 파일과 2개의 인자 필요
            fprintf(stderr, "사용법: %s print [data_binary.dat]\n", argv[0]);
            return 1;
        }
        FILE *fp = fopen(argv[2], "rb");  // 읽기 모드로 binary 파일 열기
        if (!fp) {  // 파일이 없으면 에러 출력
            perror("파일 열기 실패");
            return 1;
        }
        print_all(fp);   // 전체 데이터 출력하기
        fclose(fp);
    } else if (is_cmd(argv[1], "update")) {  // 특정 id 센서 데이터 출력하기
        if (argc != 5) {  // binary 파아ㅣㄹ과 id 필요함.
            fprintf(stderr, "사용법: %s update [data_binary.dat] [id]\n", argv[0]);
            return 1;
        }
        int id = atoi(argv[3]);   // 문자열이라 정수형으로 변환해서 id 로 사용
        int fd = open(argv[2], O_RDWR); // 파일을 읽기 모드와 쓰기 모드로 열기
	if (fd < 0) {
		perror("파일 열기 실패");
		return 1;
	}

	update (fd, id);   // 열린 fd와 id 넘겨줌

	close(fd);
    } else if (is_cmd(argv[1], "search")) {  // search를 통해 키워드 검색하기
        if (argc != 4) {  // binary 파일과 키워드 필요함
            fprintf(stderr, "사용법: %s search [data_binary.dat] [keyword]\n", argv[0]);
            return 1;
        }
        search(argv[2], argv[3]);  // binary 파일과 검색 키워드 전달
    } else {  // 잘못된 명령어 입력 시 에러 메세지 출력
        printf("알 수 없는 명령어: %s\n", argv[1]);
        printf("가능한 명령어: init, print, update, search\n");
    }
    return 0;
}

