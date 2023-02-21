#include "priorityqueue.h"
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    //create object of priroty queue class with the max nodes to be 30
    PriorityQueue myQueue(30);
    //intake the command lie argument file 
    std::string jsonfile = argv[1]; 
    //if stream the file nae
    std::ifstream file (jsonfile); 
    //allows us to parse through the file
    nlohmann::json Key_Instruction = nlohmann::json::parse(file); 
    //intializing our json variable for our output
    nlohmann::json OutputJSON;
    
    //iterator that will iterate through the json file 
    for(nlohmann::json::iterator it = Key_Instruction.begin(); it != Key_Instruction.end(); it++)
    {
        //will iterate through the entire date until we reach the 'metadata'
        if(it.key() != "metadata")
        {
            //if the json operation field says insert
            if (Key_Instruction[it.key()]["operation"] == "insert"){ 
            //intialize Key data type and store
                Key tempKey = Key_Instruction[it.key()]["key"]; 
            //insert the Key variable into the queue
                myQueue.insert(tempKey);  
            //end of if
            }
            //if the operation does not say insert
            else {
            //we remove the minimum
                myQueue.removeMin();
            //end of else
            };
            //end of if
        };
        //end of for
    };
    //after iterating through the entire file we convert the queue as a json and store it to json
    OutputJSON = myQueue.JSON();
    //print the json
    std::cout << OutputJSON.dump(2) << std::endl; 
}
 