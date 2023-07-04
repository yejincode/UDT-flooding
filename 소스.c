#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h> //���н����� ����ϴ� ������ �����쿡�� ����� �� �ֵ��� ���� winsock�� include �Ѵ�. 
#include <stdlib.h>
#include <string.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define BUFSIZE 1024
#define	PORT 10004
#define MAX_STR 13

int main() {
	// ���� ����ü, ���� ����ü, ���� �ּ� ����ü�� �Ҵ��Ѵ�.
	WSADATA winsockData; //WSADATA: ���� �ʱ�ȭ ����ü
	SOCKET clientSocket; //SOCKET: ���� ����ü
	SOCKADDR_IN serverAddr; // SOCKADDR: ���� �ּ� ����ü
	// SOCKADDR clientAddr; //client������ clientaddr ���� ����� ���� ����. (udp ����� ���)

	// �ۼ��ſ� ����� ����(buf), �ۼ��� ������ ���� ����(recvLen,sendLen), �ּ� ����ü ����(serversize)�� �����ϱ� ���� ������ �Ҵ��Ѵ�. 
	char buf[BUFSIZE];
	int recvLen;
	int sendLen;
	int serverSize;

	//IP�ּ� ��ȣȭ, ��ȣȭ
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
	
	//���� ����ü�� �ʱ�ȭ �����ش�.
	if (WSAStartup(0x202, &winsockData) == SOCKET_ERROR) {
		printf("���� �ʱ�ȭ ���� \n");
		WSACleanup();
		return;
	}
	printf("���� �ʱ�ȭ ���� \n");

	// �ּ� ����ü(serverAddr)�� ������ ���� ����(buf)�� �ʱ�ȭ ��Ų��. 
	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(buf, 0, BUFSIZE);

	// ���� �ּ� ����ü �ʱ�ȭ
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("114.70.37.17");
	serverAddr.sin_port = htons(PORT); // ���� ������ ��Ʈ ��ȣ�� 10004������ �����ߴ�.

	// ���� ���� �� ���� ���� ���� �� ���� ó��
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET) {
		printf("���� ���� ���� \n");
		WSACleanup();
		return;
	}
	printf("���� ���� ���� \n");


	// sendto �Լ��� �̿��ؼ� serverAddr�� �޽��� �����ϰ� ���� �߻��ϸ� ���� ó��
	sendLen = sendto(clientSocket, "IMHACKER_2019111394", BUFSIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));;

	if (sendLen != BUFSIZE) {
		printf("sendto() ���� \n");
		return;
	}

	//recvfrom �� �ϱ� ���� �ּ� ����ü ũ�⸦ ������ �����ϰ�, ������ �ޱ� ���� buf�� 0���� �ʱ�ȭ
	serverSize = sizeof(serverAddr);
	memset(buf, 0, BUFSIZE);

	//�����κ��� ���� �����͸� recvfrom �Լ��� ���� �ް� ���� �߻��� ���� ó��.
	recvLen = recvfrom(clientSocket, buf, BUFSIZE, 0, (struct sockaddr*)&serverAddr, &serverSize);
	if (recvLen < 0) {
		printf("recvfrom() ���� \n");
		return;
	}
	// �����κ��� ���� �����͸� ����Ѵ�. 
	printf("���� �޼���: %s \n", buf);

	// server�� ���� ���� �����Ϳ��� ip�� ��Ʈ ��ȣ�� �˾Ƴ���. 
	char* str1 = NULL;
	char* str2 = strtok_s(buf, "_", &str1); //_�� �������� ���ڿ��� �ڸ���.

	printf("�߸� ���ڿ� : %s\n", str2); //���
	printf("�ڸ��� ���� ���ڿ� : %s\n", str1);

	str2 = strtok_s(NULL, ":", &str1); //_�� �������� ���ڿ��� �ڸ���.

	printf("�߸� ���ڿ� : %s\n", str2); // str2�� ip�ּҰ� �ȴ�.
	printf("�ڸ��� ���� ���ڿ� : %s\n", str1); //str1�� port��ȣ�� �ȴ�. 

	// ���ڿ��� int�� ��ȯ�Ѵ�.
	int num;
	num = atoi(str1);


	//���� ����ü�� �ʱ�ȭ �����ش�.
	if (WSAStartup(0x202, &winsockData) == SOCKET_ERROR) {
		printf("���� �ʱ�ȭ ���� \n");
		WSACleanup();
		return;
	}
	printf("���� �ʱ�ȭ ���� \n");

	// ������ ���� ����,ip�ּ�,��Ʈ ��ȣ �ʱ�ȭ 
	memset(buf, 0, BUFSIZE);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(num);


	//10�� �ݺ��Ͽ� �����͸� ������ (UDP flooding ����)
	for (int i = 0; i < 10; i++)
	{
		// sendto �Լ��� �̿��ؼ� serverAddr�� ������(buf) �����ϰ� ���� �߻��ϸ� ���� ó��
		sendLen = sendto(clientSocket, "2019111394", BUFSIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

		if (sendLen != BUFSIZE) {
			printf("sendto() ���� \n");
			return;
		}
	}

	//������ �ݰ� ����� ������. 
	closesocket(clientSocket);
	WSACleanup();


}