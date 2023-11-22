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
#include "../include/Connection.h"
#include <unistd.h>
using namespace std;

void update(Connection *);
int main(){
	Connection *conn = new Connection(AF_INET, 5051, "192.168.42.166");
	conn->init();
	while(true){
		system("clear");
		update(conn);
		sleep(5);
	}
}
void update(Connection *conn){
	//making the table
	int colWidth = 15;
	cout << setfill('*') << setw(2*colWidth) << "*" << endl;
	cout << setfill(' ') << fixed;
	cout << setw(colWidth) << "Fog ID"<< setw(colWidth) << "Status" << endl;
	cout << setfill('*') << setw(2*colWidth) << "*" << endl;
	bool isSafe = true;
	string data = conn->crecv();
	char fid = data[0];
	char stat = data[1];
	string sd = "";
	if (stat == '1'){ sd = "\033[1;32mSAFE\033[0m\n"; }
	else{ sd = "\033[1;31mUNSAFE\033[0m\n"; }
	cout << setfill(' ') << fixed;
	cout << setprecision(0) << setw(colWidth) << (char)fid << "\t\t" << sd << endl;
}
