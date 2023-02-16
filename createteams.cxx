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
        if(it.key() == "metadata")
        {
            int numofTeams = teamData[it.key()]["metadata"];
            PriorityQueue teamQueue(numofTeams/2);
        }
        else 
        {
            //storing player 1 data
            int player1 = teamData[it.key()]["playerOne"]; //1 
            //storing player 2 data
            int player2 = teamData[it.key()]["playerTwo"]; //2
            //store the currentWinPercentage  
            currentWinPercentage = teamData[it.key()]["winPercentage"]; //53.724
            //check if the two players are already on a team 
        //this will check if we have finished going through all possible matches of player1

            if(!(TEAMS.count(player1) > 0 || TEAMS.count(player2) > 0)) //0 in map? NO 1 in map ? N)
            {
                  if(restcheck < player2)
                  { 
        //POTENTIALLY MAKE AS A FUNCTION LINE 42-52
                    restcheck = player2;
                    difference = abs(currentWinPercentage - 50);  //55-50 = 5
                    if(lowest > difference) //5 > 0 YES
                    {
                        lowest = difference; //lowest = 5
                        int bestPlayer1 = player1; // 0 
                        int bestPlayer2 = player2; // 1
                        double currentBest = currentWinPercentage; //55.11
                    } 
        //STORE THEM IN MAP AND PUT IN HEAP    
                    
                  }
                
            }

        //ELSE CONDITION TO CHECK THE PLAYER2 NUMBER HAS BEEN CHECKED AS A KEY (NOT A VALUE)
          
           
        
        
            

        }
        
    }


}
