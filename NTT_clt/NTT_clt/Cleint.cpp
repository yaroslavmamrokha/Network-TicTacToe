#include"host_clt.h"
int zx;
void DC_check(SOCKET server){
	char* DC = new char[1];
	while (1){
		if ((recv(server, DC, 1, NULL)) < 0){
			cerr << "Failed to recieve position check" << endl;
			closesocket(server);
			delete[]DC;
			exit(1);
		}
		break;
	}
	if (DC[0] == 'D'){
		cout << "Your opponent has disconnected...Closing application" << endl;
		closesocket(server);
		delete[]DC;
		exit(1);
	}
	DC[0] = 0;
	delete[]DC;
}
int Menu(){
	char status;
	cout << "Please choose your role:" << endl;
	cout << "1) Host" << endl;
	cout << "2) Client" << endl;
	cout << "3) Exit" << endl;
	status = getch();
	if (status > '3' || status < '1'){
		cout << "Bad input!" << endl;
		Sleep(1500);
		Menu();
	}

	switch (status){
	case '1':
		cout << "You choosed to be host" << endl;
		return HOST;
		break;
	case '2':
		cout << "You choosed to be client" << endl;
		return CLIENT;
		break;
	case '3':
		cout << "Exiting......Bye bye" << endl;
		exit(1);
	}
	return 0;
}

void Bad_Input(char * pos, SOCKET server, char* Field)
{
	//DC_check(server);
	while (1)
	{	
		if ((zx = recv(server, pos, 1, NULL)) < 0){
			cerr << "Failed to recieve position check" << endl;
			closesocket(server);
			exit(1);
		}
		break;
	}
	if (pos[0] == '7'){
		//DC_check(server);
		while (1){
			
			if ((zx = recv(server, Field, 9, NULL)) < 0){
				cerr << "Failed to recieve Field" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		system("CLS");
		cout << " !!!!--------------YOUR PLAYING LIKE UNDEFINED<BAD INPUT PROCSESS>--------------!!!!" << endl;
		ShowField(Field);

	}
	if (pos[0] == '8'){
		cout << "Bad position" << endl;

		int k = 0;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				cout << "  ||  " << Field[k] << "  ||  ";
				k++;
			}
			cout << endl;
		}
		cout << "Enter position: " << endl;
		k = 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				cout << "  ||  " << k << "  ||  ";
				k++;
			}
			cout << endl;
		}
		cin >> pos[0];
		if (zx = send(server, pos, 1, NULL) < 0){
			cerr << "Failed to send position" << endl;
			closesocket(server);
			exit(1);
		}
		Bad_Input(pos, server, Field);

	}
}
void main(){
	SOCKET server;
	WSADATA wData;
	int sid = 0;
	char* Field = new char[9];
	memset(Field, 0, 9);
	char id_list[255];
	int id;
	memset(id_list, 0, 255);
	int status;
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

	
	status = Menu();
	
	if (status == HOST){

		if ((connect(server, (struct sockaddr*)&serv, sizeof(serv))) < 0)
		{
			cerr << "Failed to connect to server" << endl;
			closesocket(server);
			exit(1);
		}
		getch();
			if (send(server, "1", 1, NULL) < 0){
				cerr << "Failed to send status" << endl;
				closesocket(server);
				exit(1);
			}
		
		char seid[1];
		cout << "Enter your id! " << endl;
		cin >> sid;
		seid[0] = sid;
		if (send(server, seid, 1, NULL) < 0){
			cerr << "Failed to send id" << endl; 
			closesocket(server);
			exit(1);
		}

		while (1){
			cout << "Waiting server answer" << endl;
			//DC_check(server);
			if ((zx = recv(server, ind, 1, NULL)) < 0){
				cerr << "Failed to recieve status" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}

		Host(server, Field);
	}
	if (status == CLIENT){
		if ((connect(server, (struct sockaddr*)&serv, sizeof(serv))) < 0)
		{
			cerr << "Failed to connect to server" << endl;
			closesocket(server);
			exit(1);
		}
		char pos[1];
		getch();
		if (send(server, "3", 1, NULL) < 0){
			cerr << "Failed to send status" << endl;
			closesocket(server);
			exit(1);
		}

		while (1){
				if ((zx = recv(server, id_list, 255, NULL)) < 0){
				cerr << "Failed to recieve ID list" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		int i = 0;
		cout << "Choose id " << endl;
		for (i; i < strlen(id_list); i++){
			cout << i + 1 << ") Servers ID: " << (int)id_list[i] << ". Status: Free" << endl;
		}
		cin >> id;
		pos[0] = id_list[id - 1];
		if (send(server, pos, 1, NULL) < 0){
			cerr << "Failed to send id" << endl;
			closesocket(server);
			exit(1);
		}

		//DC_check(server);
		while (1){
			cout << "Waiting server answer" << endl;
		
			if ((zx = recv(server, ind, 1, NULL)) < 0){
				cerr << "Failed to recieve status" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		Clt(server, Field);
	}
	
	closesocket(server);
}

void Clt(SOCKET server, char* Field){
	    char pos[1];
		while (1){
			system("CLS");
			cout << " !!!!--------------YOUR PLAYING LIKE CLIENT--------------!!!!" << endl;
			//DC_check(server);
			while (1){
					if ((zx = recv(server, Field, 9, NULL)) < 0){
					cerr << "Failed to recieve Field" << endl;
					closesocket(server);
					exit(1);
				}
				break;
			}
			ShowField(Field);
				cout << "Waiting servers move....." << endl;
				//DC_check(server);
				while (1){

					if ((zx = recv(server, Field, 9, NULL)) < 0){
						cerr << "Failed to recieve Field" << endl;
						closesocket(server);
						exit(1);
					}
					break;
				}
				system("CLS");
				cout << " !!!!--------------YOUR PLAYING LIKE CLIENT--------------!!!!" << endl;
				ShowField(Field);
				//DC_check(server);
				while (1){
						if ((zx = recv(server, win_check, 1, NULL)) < 0){
						cerr << "Failed to recieve wincheck" << endl;
						closesocket(server);
						exit(1);
					}
					break;
				}
				if (win_check[0] == '3'){
					cout << "DRAW!!!!" << endl;
					getch();
					exit(1);
				}
				if (win_check[0] == '6'){
					cout << "YOU WIN!!!!" << endl;
					getch();
					exit(1);
				}
				if (win_check[0] == '5'){
					cout << "YOU LOST!!!!" << endl;
					getch();
					exit(1);
				}
				//DC_check(server);
				while (1){
					cout << "Waiting servers move....." << endl;
					if ((zx = recv(server, ind, 1, NULL)) < 0){
						cerr << "Failed to recieve next" << endl;
						closesocket(server);
						exit(1);
					}
					break;
				}
			

			system("CLS");
			cout << " !!!!--------------YOUR PLAYING LIKE CLIENT--------------!!!!" << endl;
			ShowField(Field);
			cout << "Enter position: " << endl;
		 int k = 1;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					cout << "  ||  " << k << "  ||  ";
					k++;
				}
				cout << endl;
			}
			cin >> pos[0];
			if (send(server, pos, 1, NULL) < 0){
				cerr << "Failed to send position" << endl;
				closesocket(server);
				exit(1);
			}
			Bad_Input(pos, server, Field);


			//DC_check(server);
			while (1){
					if ((zx = recv(server, win_check, 1, NULL)) < 0){
					cerr << "Failed to recieve win_check" << endl;
					closesocket(server);
					exit(1);
				}
				break;
			}

			if (win_check[0] == '6'){
				cout << "YOU WIN!!!!" << endl;
				getch();
				exit(1);
			}
			if (win_check[0] == '5'){
				cout << "YOU LOST!!!!" << endl;
				getch();
				exit(1);
			}

		}
}

void ShowField(char* Field){
	int k = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			cout << "  ||  " << Field[k] << "  ||  ";
			k++;
		}
		cout << endl;
		cout << endl;
	}
}

void Host(SOCKET server, char* Field){

	char pos[1];
	
	while (1){
		system("CLS");
		cout << " !!!!--------------YOUR PLAYING LIKE HOST--------------!!!!" << endl;
		//DC_check(server);
		while (1){

			if ((zx = recv(server, Field, 9, NULL)) < 0){
				cerr << "Failed to recieve Field" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}

		
		ShowField(Field);
		cout << "Enter position: " << endl;
		int k = 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				cout << "  ||  " << k << "  ||  ";
				k++;
			}
			cout << endl;
		}
		cin >> pos[0];
		if (send(server, pos, 1, NULL) < 0){
			cerr << "Failed to send position" << endl;
			closesocket(server);
			exit(1);
		}
		Bad_Input(pos, server, Field);

		//DC_check(server);
		while (1){
			cout << "Waiting server answer" << endl;
			if ((zx = recv(server, win_check, 1, NULL)) < 0){
				cerr << "Failed to recieve win_check" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		if (win_check[0] == '3'){
			cout << "DRAW!!!!" << endl;
			getch();
			exit(1);
		}
		if (win_check[0] == '6'){
			cout << "YOU WIN!!!!" << endl;
			getch();
			exit(1);
		}
		if (win_check[0] == '5'){
			cout << "YOU LOST!!!!" << endl;
			getch();
			exit(1);
		}
		//DC_check(server);
		while (1){

			if ((zx = recv(server, Field, 9, NULL)) < 0){
				cerr << "Failed to recieve Field" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		system("CLS");
		cout << " !!!!--------------YOUR PLAYING LIKE HOST--------------!!!!" << endl;
		ShowField(Field);
		//DC_check(server);
		while (1){

			if ((zx = recv(server, win_check, 1, NULL)) < 0){
				cerr << "Failed to recieve win_check" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
		if (win_check[0] == '6'){
			cout << "YOU WIN!!!!" << endl;
			getch();
			exit(1);
		}
		if (win_check[0] == '5'){
			cout << "YOU LOST!!!!" << endl;
			getch();
			exit(1);
		}

		//DC_check(server);
		while (1){
			if ((zx = recv(server, ind, 1, 0)) < 0){
				cerr << "Failed to recieve" << endl;
				closesocket(server);
				exit(1);
			}
			break;
		}
	}

}