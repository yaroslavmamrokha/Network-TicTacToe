#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<winsock2.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include <process.h>
#define HOST 1
#define CLIENT 2
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void ShowField(char* Field);
void Host(SOCKET server, char* Field);
void Clt(SOCKET server, char* Field);
int Menu();
void DC_check(SOCKET server);
struct sockaddr_in serv;
char win_check[1];
char ind[1];
char pos[1];
#endif