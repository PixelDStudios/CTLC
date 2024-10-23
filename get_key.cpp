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

std::pair<int,int> get_key(std::string key){//sets up a function 
    int last_int_of_key_1 = key[key.length()-1];
    std::stringstream converted_key;//creates a stringstream for the making of the converted key
    for(char c: key){//loops over the characters inside the key string
        if(isalpha(c)){//checks if the character represents an int
            int to_ascii =  static_cast<int>(c);//converts the character int to its decimal value
            std::string string_to_ascii = std::to_string(to_ascii);//converts the newly converted to decimal character of the key into a string
            int sum = 0;//creates 
            for(char digit:string_to_ascii){
                int real_digit = digit - '0'; // Convert character to integer
                sum += real_digit;
            }
            converted_key<<sum;
        }
        else if(isdigit(c)&&c==last_int_of_key_1){
            converted_key<<c*3;
        }
        else{
            converted_key<<c;
        }
    }
    std::string acquired_key = converted_key.str();
    int last_int_of_key = acquired_key[acquired_key.size()-1] - '0';
    int key_for_use = std::stoi(acquired_key);
    return std::make_pair(last_int_of_key,key_for_use);
}
int main(){
    std::pair<int,int> gotten_keys = get_key("px7");
    int key = gotten_keys.second;
    std::cout<<key;
}