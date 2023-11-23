#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <unistd.h>
using namespace std;
bool halert = false;

void update();
int main(){
	while(true){
		system("clear");
		update();
		sleep(5);
	}
}
void update(){
	ifstream fin;
	fin.open("fog.conf");
	string temp, cloud;
	int fid;
	getline(fin,temp); fid = temp[0];
	getline(fin,temp);
	getline(fin,cloud); //adderres
	fin.close();
	fin.open("hstatus.dat");

	//making the table
	int colWidth = 15;
	cout << setfill(' ') << fixed;
	cout << setw(colWidth) << setw(colWidth) << "FOG ID: "<< fid << setw(colWidth) << endl;
	cout << endl;

	cout << setfill('*') << setw(2*colWidth) << "*" << endl;
	cout << setfill(' ') << fixed;
	cout << setw(colWidth) << "Helmet ID"<< setw(colWidth) << "Status" << endl;
	cout << setfill('*') << setw(2*colWidth) << "*" << endl;
	bool isSafe = true;

	while(getline(fin,temp)){
		char hid = temp[0];
		char hstatus = temp[2];
		if (hstatus == '0') isSafe = false;
		string hsp;
		if(!halert && hstatus == '1') hsp = "\033[1;32mSAFE\033[0m\n";
		else{ hsp = "\033[1;31mUNSAFE\033[0m\n"; halert = true;}
		cout << setfill(' ') << fixed;
		cout << setprecision(0) << setw(colWidth) << (char)hid << "\t\t" << hsp << endl;
	}

	//send to the cloud
	int sid = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	bzero((char*)&addr, sizeof(addr));
	struct hostent *server;
	char ca[cloud.size()];
	int index = 0;
	for(auto ii : cloud){ ca[index] = ii; index++; }
	server = gethostbyname("192.168.42.166");
	bcopy((char*)server->h_addr, (char*)&addr.sin_addr.s_addr, server->h_length);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5051);
	int cid = connect(sid, (struct sockaddr*)&addr, sizeof(addr));
	if (cid < 0) cout << "CE" << endl;
	char buffer[256];
	buffer[0] = (char)fid;
	if(isSafe) buffer[1] = '1';
	else buffer[1] = '0';
	write(sid,buffer,256);
}
