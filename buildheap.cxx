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
            //if key is not null, meaning it is present then we get the key and insert
            if (Key_Instruction[it.key()]["operation"] == "insert"){ 
                Key tempKey = Key_Instruction[it.key()]["key"]; 
                myQueue.insert(tempKey);  
                std::cout << "insertion done" << std::endl;
                KeyValuePair minNum = myQueue.min(); 
                //std::cout<< "the minimum number is " << minNum.first << std::endl; 
            }
            else {
                std::cout << "before a remove min" << std::endl; 
                
                myQueue.removeMin();
                //std::cout << "after a remove min" << std::endl; 
    
            };
        };
    };

    OutputJSON = myQueue.JSON();
    std::cout << OutputJSON.dump(2) << std::endl; 
}
 