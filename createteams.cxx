#include "priorityqueue.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

int main(int argc, char** argv) {
    //create anm object of the priority queue that has a max size of 780
    PriorityQueue playerQueue(780);
    //store json command line into string variable
    std::string jsonfile = argv[1]; 
    //ifstream the json file
    std::ifstream file (jsonfile);
    //json variable that parses the json  
    nlohmann::json Player_Data = nlohmann::json::parse(file); 
    //initialize the jsonh for the output for later
    nlohmann::json OutputJSON;

    //iterator that will loop through the json 
    for(nlohmann::json::iterator it = Player_Data.begin(); it != Player_Data.end(); it++)
    {
    //iterate through json that does not contain 'metadata' field
        if(it.key() != "metadata")
        {
        //for loop that will iterate through the json array of matches
            for(int i = 0; i < 780; i++)
            {
            //get value of win percentage of that match
                double tempWin = Player_Data[it.key()][i]["winPercentage"]; 
            //get the absolute value of 50 - tempwin
                double addWin = abs(50.000 - tempWin); 
            //the difference will be our Key
                Key tempKey = addWin; 
            //Values will be the the two players of that match
                Value tempValue(Player_Data[it.key()][i]["playerOne"], Player_Data[it.key()][i]["playerTwo"]); 
            //Create a KeyValuePair with the difference and two players
                KeyValuePair tempKVP(tempKey, tempValue); 
            //insert the KeyValuePair into the queue
                playerQueue.insert(tempKVP); 
            //end of if
            }
        //end of if
        }
    //end of for
    }
    //initilize a vector of int pairs;
    std::vector<std::pair<int, int>> finalVector; 

    //while the size is still bigger than 0, meaning we have not removed all the values yet
    while(playerQueue.size() > 0)
    {
        //we remove the min and get the value that we removed and store in minKVP
        KeyValuePair minKVP = playerQueue.removeMin();
        //Get Value and player 1 of miniKVP
        int p1 = (minKVP.second).first; 
        //Get Value and player 2 of miniKVP
        int p2 = (minKVP.second).second; 
        //store the two ints into a pair called p1p2
        std::pair<int, int> p1p2 (p1,p2);
        //store pair into vector
        finalVector.push_back(p1p2);

        //for loop that will iterate through entire queue
        for( size_t i = playerQueue.size(); i > 0; i--){
            //get the Value of the players at every node
            Value ithValue = playerQueue.getValue(i); 
            //check if either player 1 or 2 are in the vector p1p2
            if (ithValue.first == p1 || ithValue.first == p2 || ithValue.second == p1 || ithValue.second == p2) 
            {
                //if it is then we remove the that node from queue
                playerQueue.removeNode(i);
            //end of if
            }
        //end of for
        }
    //end of while
    }

    //create json that outputs 'teamstats' and an array of all pairs in the vectors
    OutputJSON["teams"] = finalVector;
    //print the outputjson to terminal
    std::cout << OutputJSON.dump(2) << std::endl; 


}
 


