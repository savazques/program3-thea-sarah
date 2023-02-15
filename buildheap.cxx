#include "priorityqueue.h"
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    PriorityQueue myQueue(30);
    std::string jsonfile = argv[1]; 
    std::ifstream file (jsonfile); 
    nlohmann::json Key_Instruction = nlohmann::json::parse(file); 
    nlohmann::json OutputJSON;
    

    for(nlohmann::json::iterator it = Key_Instruction.begin(); it != Key_Instruction.end(); it++)
    {
        if(it.key() != "metadata")
        {
            if (Key_Instruction[it.key()]["operation"] == "insert"){ 
                Key tempKey = Key_Instruction[it.key()]["key"]; 
                myQueue.insert(tempKey);  
            }
            else {
                myQueue.removeMin();
            };
        };
    };

    OutputJSON = myQueue.JSON();
    std::cout << OutputJSON.dump(2) << std::endl; 
}
 