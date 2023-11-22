#pragma once 
#include <fstream>
#include <vector>
#include <map>
class Screen
{
    public:
        void readConfig();
        void readData(std::string &, bool&);
        void display();
    private:
        int zone_;
        std::vector<int> helmet_;
        //dht, mqtt
        std::map<int,std::pair<int,int>> dht_;
        std::map<int,int> mqtt_;
};
