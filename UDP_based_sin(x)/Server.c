#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <math.h>
#define PI 3.1415921828
#define BUF_SIZE 1024
#define OPSZ 4
void ErrorHandling(char* message);
double calculate(double radian);
double deg_to_rad(int degree);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock;
	char opinfo[BUF_SIZE];
	// int result, opndCnt;
	int recvCnt;
	int degree = 0; 
	double radian, result;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_DGRAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("UDP socket creation error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY); // 127.0.0.1 로 해야하는거 아니가? 왜 되는거지?
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	clntAdrSize = sizeof(clntAdr);

	while (1)
	{
		recvCnt = recvfrom(hServSock, (char*)&degree, sizeof(int), 0, (SOCKADDR*)&clntAdr, &clntAdrSize); // &clntAdrSize); 이건 왜?
		printf("연산 요청 (%d Byte) from IP:%s Port: %d   >> ", recvCnt, inet_ntoa(clntAdr.sin_addr), ntohs(clntAdr.sin_port));
		
		radian = deg_to_rad(degree);
		result = sin(radian);
		printf("%f, %f \n", radian, result);
		sendto(hServSock, (char*)&result, sizeof(result), 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr)); // sizeof(clntAdr) recvfrom 이랑 다름.
		

	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}
double deg_to_rad(int degree) {
	double radian;
	radian = (PI / 180) * degree;
	return radian;
}
double calculate(double radian)
{
	int result = sin(radian);
	int i = 1;

	// 계산...
	return result;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
