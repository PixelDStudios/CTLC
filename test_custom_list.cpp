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
    Addition,
    Overwrite,
    Implement,
    Unknown
};

std::string hexed(std::vector<std::string> commands){
    int to_encrypt_0=2,int_amount=0, number_char_count = 0,value=1;
    std::string command;
    for(std::string s:commands){
        //TODO remove " " from s
        std::stringstream int_type_string;
        int_amount=0;
        char first_char_num = s[1];
        if(isdigit(first_char_num)){
            for(char ch:s){
            
                if(isdigit(ch)){
                    int_type_string<<ch;
                    value = std::stoi(int_type_string.str());
                    number_char_count+=1;
                    int_amount+=1;
                }
                else if(!isdigit(ch)&&number_char_count>0){
                    break;
                }

            }
        }
        
        
        else if(s=="mul"){
            command = "mul";
        }
        else if(s=="div"){
            command = "div";
        }
        else if(s=="add"){
            command = "add";
        }
        else if(s=="sub"){
            command = "sub";
        }
        if(int_amount>0){
            if(command=="mul"){
                to_encrypt_0 = to_encrypt_0*value;
                
            }
            if(command=="sub"){
                to_encrypt_0 = to_encrypt_0-value;
            }
            if(command=="add"){
                to_encrypt_0 = to_encrypt_0+value;
            }
            if(command=="div"){
                to_encrypt_0 = to_encrypt_0/value;
            }
            int_amount = 0;
        }
    }

    return std::to_string(to_encrypt_0);
}

Command getCommand(const std::string& choice_) {
    if (choice_ == "read") return Command::Read;  
    if (choice_ == "overwrite") return Command::Overwrite;
    if (choice_ == "addition") return Command::Addition;
    if (choice_ == "implement") return Command::Implement;
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
            case Command::Implement:{
                std::ifstream command_file_0("commands.txt");
                while(std::getline(command_file_0,read_string)){
                    std::cout<<read_string;
                }
                std::vector<std::string> encr_commands;
                std::stringstream word;
                for(char c:read_string){
                    if(c==' '){
                        encr_commands.push_back(word.str());
                        word.str("");
                    }
                    word<<c;
                }
                command_file_0.close(); 
                std::cout<<hexed(encr_commands);
                break;
            }
            case Command::Overwrite:{
                std::getline(std::cin,input);
                std::ofstream command_file_0("commands.txt");
        
                command_file_0<<input;
                command_file_0.close();
                
                break;
            }
            case Command::Addition:{
                std::getline(std::cin,input);
                std::ofstream command_file_0("commands.txt",std::ios::app);
        
                command_file_0<<" "<<input;
                command_file_0.close();
                
                break;
            }
            default:{
                std::cout<<"Invalid command"<<"\n";
                break;
            }
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

