TARGET = main                # 최종 파일
SRCS = main.c print.c        # 소스 파일 목록
OBJS = $(SRCS: .C = .0)      # 목적 파일 목록
HEADERS = device.h print.h          #main.c와 print.c가 공통으로 참조하는  헤더 파일
cc = gcc       # 컴파일러
CFLAGS = -Wall -g       # 옵션(-Wall 모든 경고, -g 디버깅)
$(TARGET): $(OBJS)     # 빌드 규칙
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)     # 개별 파일 규칙
	$(CC) $(CFLAGS) -c $< -o $@

clean:  # 중간 결과물 삭제
	rm -f $(OBJS) $(TARGET)


