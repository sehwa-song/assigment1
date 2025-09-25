#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device.h"
#include "print.h"

int is_cmd(const char *input, const char *cmd) {
    return strcmp(input, cmd) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s 실행 방법: [명령어] [파일명]\n", argv[0]);
        fprintf(stderr, "가능한 명령어: init, print, update, search\n");
        return 1;
    }

    if (is_cmd(argv[1], "init")) {
        if (argc != 4) {
            fprintf(stderr, "사용법: %s init [data.txt] [data_binary.dat]\n", argv[0]);
            return 1;
        }
        init(argv[2], argv[3]);
    } else if (is_cmd(argv[1], "print")) {
        if (argc != 3) {
            fprintf(stderr, "사용법: %s print [data_binary.dat]\n", argv[0]);
            return 1;
        }
        FILE *fp = fopen(argv[2], "rb");
        if (!fp) {
            perror("파일 열기 실패");
            return 1;
        }
        print_all(fp);
        fclose(fp);
    } else if (is_cmd(argv[1], "update")) {
        if (argc != 4) {
            fprintf(stderr, "사용법: %s update [data_binary.dat] [id]\n", argv[0]);
            return 1;
        }
        int id = atoi(argv[3]);
        update(argv[2], id);
    } else if (is_cmd(argv[1], "search")) {
        if (argc != 4) {
            fprintf(stderr, "사용법: %s search [data_binary.dat] [keyword]\n", argv[0]);
            return 1;
        }
        search(argv[2], argv[3]);
    } else {
        printf("알 수 없는 명령어: %s\n", argv[1]);
        printf("가능한 명령어: init, print, update, search\n");
    }
    return 0;
}

