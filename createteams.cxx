#include "priorityqueue.h"
#include <fstream>
#include <iostream>
#include "json.hpp"




int main(int argc, char** argv) {
    std::string jsonFile = argv[1];
    std::ifstream file (jsonFile); 
    nlohmann::json teamData = nlohmann::json::parse(file); 
    std::map<int,int> TEAMS; 
    double currentWinPercentage; 
    double difference;
    int restcheck = 0; 
    double lowest = 51.0;
    

    for(nlohmann::json::iterator it = teamData.begin(); it != teamData.end(); it++)
    {
        if(it.key() != "metadata")
        {
            for (int i  = 0; i < 40; i ++)
            {
                nlohmann::json o = teamData[it.key()][i] ;
                std::cout << o["playerTwo"]; 

                
            }
            
        }
        

          
    }


}
