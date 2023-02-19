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
    PriorityQueue teamPlayerQueue(20);
  
    double lowest = 51.0;
    
    //while the sizeoftheque is still less than the teams
    while(teamPlayerQueue.size() < 20)
    {
        for(nlohmann::json::iterator it = teamData.begin(); it != teamData.end(); it++)
        {
            if(it.key() != "metadata")
            {
                for (int i  = 0; i < 40; i ++)
                {
                    nlohmann::json round = teamData[it.key()][i] ;
                    int player1 = round["playerOne"]; 
                    int player2 = round["playerTwo"]; 
                    double difference = abs(round["winPercentage"] - 50); 

                    if(lowest > difference)
                    {
                        lowest = difference;
                        Value players(player1,player2);
                        Key heapValue = lowest; 
                        KeyValuePair kvp (heapValue,players);
                        teamPlayerQueue.insert(kvp);
                        
                    }

                    
                }
                
            }
            
                
        }
        
    }




}
