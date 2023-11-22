#include "./include/Connection.h"
#include "./include/Screen.h"
#include <iostream>
#include <thread>

std::string data;
bool changed = false;

void updateValue(){
    Connection *conn = new Connection(AF_INET, 5000, "192.168.42.166");
    conn->init();
	while(1){
    	data = conn->recv();
		changed = true;
		std::cout << "Data: " << data << std::endl;
	}
}

void update(Screen *s){
	while(true){
		s->readData(data, changed);
	}
}

int main(){
	std::thread updateThread(updateValue);

	Screen *s = new Screen();
	s->readConfig();
	std::thread rdata(update, s);

	while(1){
		s->display();
		sleep(2);
	}
}
