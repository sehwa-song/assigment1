#ifndef DEVICE_H
#define DEVICE_H

typedef struct {
    int id;
    char name[50];
    char status[10];
} Sensor;   // print.c와 main.c 둘 다 구조체 Sensor를 알아야 됨. 중복정의 되면 안되므로 device.h라는 공용 헤더 파일에 넣음.

#endif

