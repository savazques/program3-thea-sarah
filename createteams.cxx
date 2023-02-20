#include "priorityqueue.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

int main(int argc, char** argv) {
    PriorityQueue playerQueue(780);
    std::string jsonfile = argv[1]; 
    std::ifstream file (jsonfile); 
    nlohmann::json Player_Data = nlohmann::json::parse(file); 
    nlohmann::json OutputJSON;

    typedef double                  Key;
    typedef std::pair<int, int>     Value;
    typedef std::pair<Key, Value>   KeyValuePair; 
    

    for(nlohmann::json::iterator it = Player_Data.begin(); it != Player_Data.end(); it++)
    {
        if(it.key() != "metadata")
        {
            for(int i = 0; i < 780; i++)
            {
                double tempWin = Player_Data[it.key()][i]["winPercentage"]; 
                double addWin = abs(50.000 - tempWin); 
                Key tempKey = addWin; 
                Value tempValue(Player_Data[it.key()][i]["playerOne"], Player_Data[it.key()][i]["playerTwo"]); 
                KeyValuePair tempKVP(tempKey, tempValue); 
                playerQueue.insert(tempKVP); 
            }
        }
    }

    std::vector<std::pair<int, int>> finalVector; 

    while(playerQueue.size() > 0)
    {
        KeyValuePair minKVP = playerQueue.removeMin();
        //inser to to json
        int p1 = (minKVP.second).first; 
        int p2 = (minKVP.second).second; 
        std::pair<int, int> p1p2 (p1,p2);
        finalVector.push_back(p1p2);

        // now to check if its in the other nodes 
        // come back to
        for( size_t i = playerQueue.size(); i > 0; i--){
            Value ithValue = playerQueue.getValue(i); 
            if (ithValue.first == p1 || ithValue.first == p2 || ithValue.second == p1 || ithValue.second == p2) 
            {
                playerQueue.removeNode(i);
            }
        }
    }


    OutputJSON["teamStats"] = finalVector;
    std::cout << OutputJSON.dump(2) << std::endl; 


}
 


