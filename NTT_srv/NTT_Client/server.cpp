#include "Server.h"
int zx;

void DC_check(SOCKET srv, SOCKET clt, int role){
	if (role == HOST){
		closesocket(srv);
		if (send(clt, "D", 1, NULL) < 0){
			cerr << "Failed to send DC status" << endl;
			return;
		}
		closesocket(clt);
	}
	if (role == CLIENT){
		closesocket(clt);
		if (send(srv, "D", 1, NULL) < 0){
			cerr << "Failed to send DC status" << endl;
			return;
		}
		closesocket(srv);
	}
}
void not_DC(SOCKET srv, SOCKET clt){
	if (send(clt, "K", 1, NULL) < 0){
		cerr << "Failed to send DC status" << endl;
		return;
	}if (send(srv, "K", 1, NULL) < 0){
		cerr << "Failed to send DC status" << endl;
		return;
	}
}

void closesockets(SOCKET srv, SOCKET clt){

	closesocket(srv);
	closesocket(clt);
}





void Server_info(Id* nxt){
	cout << "Host id: " << (int)nxt->host_id << endl;
	if ((int)nxt->status == 7){
		cout << "Host Status: BUSY"<< endl; 
	}
	else{
		cout << "Host Status: FREE" << endl;
	}
	cout << "++++++++++++++++++++++++++" << endl;
}
void Status(SOCKET srv, SOCKET clt){
	if (send(srv, "1", 1, NULL) < 0){
		cerr << "Failed to send Game status" << endl;
		closesockets(srv, clt);
		return; //DC_check(srv, clt,HOST);
	}
	//not_DC(srv, clt);

	if (send(clt, "1", 1, NULL) < 0){
			cerr << "Failed to send Game status" << endl;
			closesockets(srv, clt);
			return; //DC_check(srv, clt, CLIENT);
		}
	//not_DC(srv, clt);
}
	
	
void Win_Status(SOCKET srv, SOCKET clt, char* clt_win, char* serv_win){
	if (send(clt, clt_win, strlen(clt_win), NULL) < 0){
		cerr << "Failed to send win check" << endl;
		closesockets(srv, clt);
		return; //DC_check(srv, clt, CLIENT);
	}
	//not_DC(srv, clt);
	if (send(srv, serv_win, strlen(serv_win), NULL) < 0){
		cerr << "Failed to send win check" << endl;
		closesockets(srv, clt);
		return; //DC_check(srv, clt, HOST);
	}
	//not_DC(srv, clt);
}
void Fields(SOCKET srv, SOCKET clt, char* Field){
	
	if (send(srv, Field, 9, NULL) < 0){
		cerr << "Failed to send Game Field" << endl; 
		closesockets(srv, clt);
		return; //DC_check(srv, clt, HOST);
	}
	//not_DC(srv, clt);
	if (send(clt, Field, 9, NULL) < 0){
		cerr << "Failed to send Game Field" << endl;
		closesockets(srv, clt);
		return; //DC_check(srv, clt, CLIENT);
		
	}
	//not_DC(srv, clt);
}

int pos_check(char pos, char* Field){
	
	int i = 0;
	if (pos < '1' || pos > '9'){
		return BAD_INPUT;
	}
	post = pos - '0';
	if (post != 0){
		post = post - 1;
	}
	if (Field[post] == 32){
		return OKAY;
	}
	else{
		return BAD_INPUT;
	}
}
int check(char* Field)					//Win check function
{
	int i = 0;
	int count = 0;
	if (Field[0] != 32 && Field[0]== Field[4] && Field[4] == Field[8]){ // Diag \    /
		return 1;
	}
	if (Field[0] != 32 && Field[0]== Field[3] && Field[3]== Field[6]){ // Left
		return 1;
	}
	if (Field[0]!= 32 && Field[0]== Field[1] && Field[1] == Field[2]){ // Top
		return 1;
	}
	if (Field[1] != 32 && Field[1] == Field[4] && Field[4] == Field[7]){ // |
		return 1;
	}
	if (Field[2] != 32 && Field[2] == Field[5] && Field[5] == Field[8]){ // Right
		return 1;
	}
	if (Field[2] != 32 && Field[2] == Field[4] && Field[4] == Field[6]){ // Diag /
		return 1;
	}
	if (Field[3] != 32 && Field[3] == Field[4]&& Field[4] == Field[5]){ // -
		return 1;
	}
	if (Field[6] != 32 && Field[6] == Field[7]&& Field[7] != Field[8]){ // Bottom
		return 1;
	}
	for (i; i < 9; i++){
		if (Field[i] == 32)
		count += 1;
	}

	if (count == 0){
		return 3;
	}
	return 0;
}

void Game(Id* nxt, SOCKET cl, char* Field){
	char position[1];
		while (1){
		//host turn
			
		Fields(nxt->clts, cl, Field);
		checky(position, Field, nxt, cl);

		if (check(Field) == 1){
			Win_Status(nxt->clts, cl, "5", "6");
			break;
		}
		if (check(Field) == 3){
			Win_Status(nxt->clts, cl, "3", "3");
			break;
		}
		else{
			if (send(nxt->clts, "4", 1, NULL) < 0){
				cerr << "Failed to send win check" << endl; 
				closesockets(nxt->clts, cl);
				return; //DC_check(nxt->clts, cl, HOST);
				}
			//not_DC(nxt->clts, cl);
			if (send(cl, "4", 1, NULL) < 0){
				cerr << "Failed to send win check" << endl;
				closesockets(nxt->clts, cl);
				return; //DC_check(nxt->clts, cl, CLIENT);
			}
			//not_DC(nxt->clts, cl);
			
		}
		if (send(cl, "1", 1, NULL) < 0){
			cerr << "Failed to send win check" << endl;
			closesockets(nxt->clts, cl);
			return; //DC_check(nxt->clts, cl, CLIENT);;
		}
		//not_DC(nxt->clts, cl);
		
		//client turn
		checky2(position, Field, nxt, cl);
		if (check(Field) == 1){
			Win_Status(nxt->clts, cl, "6", "5");
			break;
		}
		if (check(Field) == 2){
			Win_Status(nxt->clts, cl, "3", "3");
			break;
		}
		else{
			if (send(nxt->clts, "4", 1, NULL) < 0){
				cerr << "Failed to send win check" << endl;
				closesockets(nxt->clts, cl);
				return; //DC_check(nxt->clts, cl, HOST);
			}
			//not_DC(nxt->clts, cl);
			if (send(cl, "4", 1, NULL) < 0){
				cerr << "Failed to send win check" << endl;
				closesockets(nxt->clts, cl);
				return;//DC_check(nxt->clts, cl, CLIENT);
			}
			//not_DC(nxt->clts, cl);
		}
		if (send(nxt->clts, "1", 1, NULL) < 0){
			cerr << "Failed to send win check" << endl;
			closesockets(nxt->clts, cl);
			return; //DC_check(nxt->clts, cl, HOST);
		}
		//not_DC(nxt->clts, cl);
	}

}
void checky2(char* position, char* Field, Id* nxt, SOCKET cl){
	while (1){
	if ((zx = recv(cl, position, 1, NULL)) < 0){
		cerr << "Failed to recieve position" << endl;
		return;
	}
	break;
}
	if (pos_check(position[0], Field) == BAD_INPUT){
		if (send(cl, "8", 1, NULL) < 0){
			cerr << "Failed to send position check" << endl;
			closesockets(nxt->clts, cl);
			return; //DC_check(nxt->clts, cl, CLIENT);;
		}
		//not_DC(nxt->clts, cl);
		checky2(position, Field, nxt, cl);
	}

if (pos_check(position[0], Field) == OKAY){
	Field[post] = '0';
	if (send(cl, "7", 1, NULL) < 0){
		cerr << "Failed to send position check" << endl;
		closesockets(nxt->clts, cl);
		return;//DC_check(nxt->clts, cl, CLIENT);
	}
	//not_DC(nxt->clts, cl);
	Fields(nxt->clts, cl, Field);
	}
}


void checky(char* position, char* Field, Id* nxt, SOCKET cl){
	while (1){
		if ((zx = recv(nxt->clts, position, 1, NULL)) < 0){
			cerr << "Failed to recieve position" << endl;
			return;
		}
		break;
	}

	if (pos_check(position[0], Field) == BAD_INPUT){
		if (send(nxt->clts, "8", 1, NULL) < 0){
			cerr << "Failed to send position check" << endl;
			closesockets(nxt->clts, cl);
			return; //DC_check(nxt->clts, cl, HOST);
		}
		//not_DC(nxt->clts, cl);
		checky(position, Field, nxt, cl);
	}  

	if (pos_check(position[0], Field) == OKAY){
		Field[post] = 'X';
		if (send(nxt->clts, "7", 1, NULL) < 0){
			cerr << "Failed to send position check" << endl;
			closesockets(nxt->clts, cl);
			return; //DC_check(nxt->clts, cl, HOST);
		}
		//not_DC(nxt->clts, cl);
		Fields(nxt->clts, cl,Field);
	}

	
}

void Start_Game(char* answer, SOCKET clt, char* Field){
	Id* nxt = host;
	SOCKET cl = clt;
	while (nxt->host_id != answer[0]){
		if (nxt->status != FREE && nxt->status != BUSY && nxt->status != -1){
			break;
		}
		nxt += sizeof(Id);
	}

	memset(Field, 32, 9);
	nxt->status = BUSY;
	Status(nxt->clts, cl);
	Server_info(nxt);
	Game(nxt, cl, Field);
	closesocket(nxt->clts);
	closesocket(cl);
	nxt->host_id = -1;
	nxt->status = -1;
	
}

void Free_ID_list(){
	Id* next = host;
	int i = 0;
	memset(id_list, 0, 255);
	while (1){
		if (next->status != FREE && next->status != BUSY && next->status != -1){
			break;
		}
			if (next->status == FREE){
				id_list[i] = next->host_id;
				i++;
			}
			next += sizeof(Id);
	}
	
	
}
DWORD WINAPI Host_hand(void* clients){
	SOCKET clt = (SOCKET)clients;
	char answer[1];
	int size;
	char Field[9];
	char id[1];
	Free_ID_list();
	if (send(clt, id_list, 255, NULL) < 0){
			cerr << "Failed to send id list" << endl;
			closesocket(clt);
			return 0;
		}
		while (1){
			if ((zx = recv(clt, answer, 1, NULL)) < 0){
				cerr << "Failed to recive choosen id" << endl;
				return 0;
			}
			break;
		}
		Start_Game(answer, clt, Field);
		return 0;
}



void main(){
	SOCKET server, clients;
	WSADATA wData;
	host = hosts;
	char id[1];
	char status[4];
	
	memset(status, 0, 4);
	struct sockaddr_in serv, other;
	if (WSAStartup(MAKEWORD(2, 2), &wData) != 0)
	{
		printf("Failed\n");
		exit(EXIT_FAILURE);
	}
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cerr << "Failed to create socket" << endl;
		exit(1);	
	}
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(7777);
	if (bind(server, (struct sockaddr*)&serv, sizeof(serv))<0){
		cerr << "Bind failed" << endl;
		exit(1);
	}

	if (listen(server, 10) < 0){
		cerr << "Failed to listen socket" << endl;
		exit(1);
	}
	int clt_size = sizeof(other);
	cout << "Waiting connections" << endl;
	if ((clients = accept(server, (struct sockaddr*)&other, &clt_size)) != INVALID_SOCKET)
	{
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "Connected ip: " << inet_ntoa(other.sin_addr) << endl;
	}
/*	while (1){
		cout << "Waiting connections" << endl;
		if ((clients = accept(server, (struct sockaddr*)&other, &clt_size)) != INVALID_SOCKET)
		{
			cout << "++++++++++++++++++++++++++" << endl;
			cout << "Connected ip: " << inet_ntoa(other.sin_addr) << endl;
			Sleep(1000);
			while (1){
				cout << "Waiting response" << endl;
				if ((zx = recv(clients, status, 4, 0)) < 0){
					cerr << "Failed to recive status" << endl;
					printf("failed with error: %ld\n", WSAGetLastError());
					closesocket(clients);
					exit(1);
				}
				break;
			}
			if (status[0] == '3'){
				CreateThread(0, 0, Host_hand, (void*)clients, 0, 0);
			}
			else{
				while (1){
					if ((zx = recv(clients, id, 1, 0)) < 0){
						cerr << "Failed to recive ID" << endl;
						break;
					}
					hosts->clts = clients;
					hosts->host_id = id[0];
					hosts->status = FREE;
					hosts += sizeof(Id);
					break;
				}
				

			}
		}else{
			cerr << "Failed to accept new connection" << endl;
			
		}
		

		
	}*/
	closesocket(server);
	WSACleanup();
	delete[]id_list;
	delete host;
	delete hosts;

}

