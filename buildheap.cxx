#include "priorityqueue.h"
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv) {

    PriorityQueue myQueue(30); 
    std::string jsonfile = argv[1]; 
    std::ifstream file (jsonfile); 
    nlohmann::json Key_Instruction = nlohmann::json::parse(file); 

    for(nlohmann::json::iterator it = Key_Instruction.begin(); it != Key_Instruction.end(); it++)
    {
        if(it.key() != "metadata")
        {
            //nlohmann::json d = Key_Instruction[it.key()];
            //if the
            if (!Key_Instruction[it.key()]["key"].is_null()){
                
                Key tempKey = Key_Instruction[it.key()]["key"];  
                myQueue.insert(tempKey); 
            }
            else {
                myQueue.removeMin();
            };
        };
    };
    nlohmann::json OutputJSON; 
    OutputJSON = myQueue.JSON(); 
    std::cout << OutputJSON.dump(2) << std::endl; 
}
