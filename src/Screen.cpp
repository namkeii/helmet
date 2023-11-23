#include "../include/Screen.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

bool isInt(std::string s){
    for(int c_s : s){
        if (!isdigit(c_s)){
            return false;
        }
    }
    return true;
}

void Screen::readConfig(){
    std::fstream config;
    config.open("./fog.conf", std::ios::in);

    //for zone number
    config >> zone_;

    //for number of helmets (kinda lamelol)
    int no;
    config >> no;
    //for helmet numbers
    while(no--){
        int temp;
        config >> temp;
        helmet_.push_back(temp);
        dht_[temp] = {0,0};
        mqtt_[temp] = 0;
    }
}

void Screen::readData(std::string & data, bool & changed){
    if (changed){
        std::string temp = "";
        int count = 0;
        int arr[4] = {0};
        for(int c_d : data){
            if (c_d == ' '){ 
                reverse(temp.begin(), temp.end());
                if (isInt(temp)){ arr[count] = stoi(temp); }
                count++; temp = "";
            }
            else{ temp += c_d;}
            if(count==4) break;
        }
        if (arr[3] == 0){ arr[3] = stoi(temp); }
        //updating the values
        dht_[arr[3]] = {arr[0],arr[1]};
        mqtt_[arr[3]] = arr[2];
        /*
        for(auto h : helmet_){
            std::cout << h << "n" << mqtt_[h] << " " <<
            dht_[h].first << " " << dht_[h].second << std::endl;
        }
        */
        changed = false;
    }
}

void Screen::display(){
    std::cout << "Helmet Status" << std::endl;
    for(auto h : helmet_){
        std::cout << h << " " << mqtt_[h] << " " <<
          dht_[h].first << " " << dht_[h].second << std::endl;
    }
    std::cout << "****************************" << std::endl;
    std::cout << std::endl;
    //updating the external file
    std::ofstream fout;
    fout.open("hstatus.dat");
    for(auto h : helmet_){
        fout << h << " ";
        if (mqtt_[h] > 550) fout << 0 << std::endl;
        else fout << 1 << std::endl;
    }
}