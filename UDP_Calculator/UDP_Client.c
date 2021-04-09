#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	int degree;
	double result;
	SOCKADDR_IN servAdr;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	// 전송 프로토콜 UDP 설정 SOCK_DGRAM, 
	hSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	// 720, 5 => 세밀
	while (1) {
		for (int i = 0; i < 360; i += 10) {
			degree = i;
			// printf("%d\n", degree);
			sendto(hSocket, (char*)&degree, sizeof(int), 0, (SOCKADDR*)&servAdr, sizeof(servAdr));
			recv(hSocket, (char*)&result, sizeof(result), 0);
			// printf("서버로부터 들어온 결과 : %f \n ", result);
			result = result * 20 + 20; // 야~ [-1,1] [0,40]
			// printf("%f", result);
			for (int j = 0; j < (int)result; j++) {
				printf("-");
			}
			printf("O");
			printf("\n");
		}
	}


	//for (int i = 0; i < 40; i += 1) {
	//	printf("-");
	//	if 
	//}
	

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
