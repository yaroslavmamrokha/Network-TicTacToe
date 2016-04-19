#ifndef SERVER_H
#define SERVER_H
#include<iostream>
#include<winsock2.h>
#include<windows.h>
#include<string.h>
#include <process.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
#define FREE 6
#define HOST -10
#define CLIENT -11
#define BUSY 7
#define BAD_INPUT -1
#define NOT_USED '6'
#define WAIT_CONNECT 9
#define USED '5'
#define OKAY 8

int post;
char* id_list = new char[255];
struct Id{
	SOCKET clts;
	char host_id;
	char status;

};
Id* host = new Id;
Id* hosts = new Id;
void checky(char*, char*, Id*, SOCKET);
void checky2(char*, char*, Id*, SOCKET);
void Server_info(Id*);
void Status(SOCKET, SOCKET);
void Win_Status(SOCKET, SOCKET, char*, char*);
void Fields(SOCKET, SOCKET, char*);
int pos_check(char, char*);
DWORD WINAPI Host_hand(void*);
void DC_check(SOCKET srv, SOCKET clt, int role);
void not_DC(SOCKET srv, SOCKET clt);

int check(char*);
void Game(Id*, SOCKET, char*);
void Start_Game(char*, SOCKET, char*);
void Free_ID_list();
#endif
