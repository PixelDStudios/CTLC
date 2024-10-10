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
    Implement,
    Unknown
};

std::string hexed(std::vector<std::string> commands){
    int to_encrypt_0=2,int_amount=0;
    std::string command;
    for(std::string s:commands){
        std::stringstream int_type_string;
        int_amount=0;
        int string_len = s.length();
        for(char ch:s){
            if(isdigit(ch)){
                int_type_string<<ch;
                int_amount+=1;
            }
            else{
                break;
            }
        }
        int value = std::stoi(int_type_string.str());
        if(s=="multiply"){
            command = "multiply";
        }
        if(s=="divide"){
            command = "divide";
        }
        if(s=="addition"){
            command = "addition";
        }
        if(s=="subtract"){
            command = "subtract";
        }
        else if(int_amount==string_len){
            if(command=="multiply"){
                to_encrypt_0 = to_encrypt_0*value;
            }
            if(command=="subtract"){
                to_encrypt_0 = to_encrypt_0-value;
            }
            if(command=="addition"){
                to_encrypt_0 = to_encrypt_0+value;
            }
            if(command=="divide"){
                to_encrypt_0 = to_encrypt_0/value;
            }
        }
    }

    return std::to_string(to_encrypt_0);
}

Command getCommand(const std::string& choice_) {
    if (choice_ == "read") return Command::Read;  
    if (choice_ == "overwrite") return Command::Overwrite;
    if (choice_ == "add") return Command::Add;
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

