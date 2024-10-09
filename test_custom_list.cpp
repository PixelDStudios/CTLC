#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <bits/stdc++.h>

enum class Command{
    Read,
    Add,
    Overwrite,
    Unknown
};
Command getCommand(const std::string& choice_) {
    if (choice_ == "read") return Command::Read;  
    if (choice_ == "overwrite") return Command::Overwrite;
    if (choice_ == "add") return Command::Add;    
    return Command::Unknown;
}
int main(){
    
    
    std::string input,read_string,choice;
    
    
    
    while(true){
        std::cout<<"\n";
        std::cout<<"Enter choice: ";
        std::cin>>choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(getCommand(choice)){
            case Command::Read:{
                
                std::ifstream command_file_0("commands.txt");
        
                while(std::getline(command_file_0,read_string)){
                    std::cout<<read_string;
                }
                command_file_0.close(); 
                
                break;
            }
            case Command::Overwrite:{
                std::getline(std::cin,input);
                std::ofstream command_file_0("commands.txt");
        
                command_file_0<<input;
                command_file_0.close();
                
                break;
            }
            case Command::Add:{
                std::getline(std::cin,input);
                std::ofstream command_file_0("commands.txt",std::ios::app);
        
                command_file_0<<" "<<input;
                command_file_0.close();
                
                break;
            }

        }
    }
    
    
    

    
    /*
    for(int i = 0;i<input.length();i++){
        if(input[i]==' '||i==input.length()-1){
            word.str("");
            dynamic_list.push_back(ss.str());
        }
        ss<<input[i];
    }
    std::ofstream command_file_0("commands.txt");
    command_file_0<<"";
    command_file_0.close();
    
    for(std::string s:dynamic_list){
        command_file_0<<s;
    }
    command_file_0.close();
    */
}
