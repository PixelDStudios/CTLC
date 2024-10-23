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
#include <cmath>



std::string replace_equal_digits(int keyd_,int last_int_of_key_){//makes a function for equal ints in the encrypted string to be replaced by a symbol
    std::string keyd_string = std::to_string(keyd_);//converts one encrypted hexadeciaml part of the whole encrypted string to a string
    std::stringstream new_replaced_symbol_stringstream;//creates a new stringstream in which to replace the ints in 
    char last_int_of_key = last_int_of_key_ + '0';//converts the last_int_of_key to a char data type
    for(char c:keyd_string){//loops over each character in the keyd string
        if(isdigit(c)&&c==last_int_of_key){//checks if the character represents an int and if it is equal to the last int of the converted key
            new_replaced_symbol_stringstream<<"@";//adds a string symbol to the stringsream
        }
        else{//if the character is not equal to the last int of the converted key
            new_replaced_symbol_stringstream<<c;//adds the same value to the stringstream
        }
    }
    std::string new_replaced_symbol_string = new_replaced_symbol_stringstream.str();//converts the stringstream to a string
    return new_replaced_symbol_string;//returns the new string
}


std::string encrypt_to_hex_decimal(std::string to_encrypt, std::string key,std::string symbol){//main function to encrypt the "to_decrypt" text with the "key" as the key
    std::stringstream end_string;//sets up a stringstream in which all of the encrypted parts of the text will be inserted doubleo
    std::stringstream converted_to_hex;//sets up a seperate stringstream in which all of the characters of the original string will be converted to hex
    
    
    /*
    double og_size = to_encrypt.length();//saves the size of the og string to be used later in decryption
    */
    for(char character:to_encrypt){//loops over the characters in the original string
        converted_to_hex<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<double>(static_cast<unsigned char>(character));//formats a hex value of a max length of 2 with the filler being 0 and first casts character to unsigned char and then to an double
    }
    to_encrypt = converted_to_hex.str();//replaces the original "to_decrypt" string with the newly converted hex string
    
    
    double last_double_of_key = 7;
    double key_for_use = 27422399;
    //converts the character in char_list doubleo an double
    double extra_encr = 1;
    if(to_encrypt.length()>1){
        
        for(double i = 0;i<to_encrypt.length()*2-1;i++){
            if(i<to_encrypt.size()-1){
                if(isdigit(to_encrypt[i])){
                    if(isdigit(to_encrypt[i+1])){

                        double num_1 = (to_encrypt[i] - '0') * key_for_use;
                            
                       
                        double num_2 =  (to_encrypt[i + 1] - '0') * (i+1);
                        
                        
                        end_string<<num_1<<"&"<<num_2<<"_";
                        i++;
                    }
                    if(isalpha(to_encrypt[i+1])){
                        if(std::fmod(key_for_use, 2.0)==0){
                            extra_encr = 3;
                        }
                        else{
                            extra_encr = 2;
                        }
                        double keyd = (to_encrypt[i] - '0')*key_for_use;

                        keyd = keyd *extra_encr;
                        keyd = keyd *(i+extra_encr);
                        
                        std::string keyd_gone_over = replace_equal_digits(keyd,last_double_of_key);
                        end_string<<keyd_gone_over<<to_encrypt[i+1];
                        
                        i++;
                    }
                }
            }
            else{
                end_string<<to_encrypt[i]*key_for_use;
            }
        }
    }
    else{
        std::cout<<"Error: password too short";
    }
    std::string pre_final = end_string.str();
    end_string<<"*";
    
    std::string final_result = end_string.str();
    
    return final_result;
}


int main(){
    int choice;
    std::string encryption_key;
    std::cout<<"Enter encryption key: ";
    std::cin>>encryption_key;
    std::cout<<"Enter 1 for encryption, 2 for decryption: ";
    std::cin>>choice;
    

    if(choice==1){
        std::cout<<"Enter what is to be encrypted: ";
        std::string to_encrypt;
        std::cin>>to_encrypt;
        std::cout<<encrypt_to_hex_decimal(to_encrypt,encryption_key,"@")<<"\n";
        system("pause");
    }
}