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

std::string decrypt(std::string to_decrypt,std::string key){
    std::pair<int,int> gotten_keys = get_key(key);
    int last_int_of_key = gotten_keys.first;
    int key_for_use = gotten_keys.second;
    to_decrypt = replace_equal_symbols(last_int_of_key,to_decrypt);
    int length_of_to_decrypt = return_length_of_decryptable_string(to_decrypt);
    std::stringstream end_string;
    std::stringstream double_digit_encr;
    int extra_encr = 1;
    int k = 0;
    if(length_of_to_decrypt>1){
        for(int i = 0;i<length_of_to_decrypt*2-1;i++){
            if(i<to_decrypt.size()-1){
                if(isdigit(to_decrypt[i])){
                    for(int j = i+1;;j++){
                        if(isdigit(to_decrypt[j])){
                            double_digit_encr<<to_decrypt[j];
                        }
                        else if(isalpha(to_decrypt[j])){
                            i+=j;
                            k+=1;
                            break;
                        }
                    }
                    
                }
            }
        }
    }
    //45448a1748&6_1748&5_2185&0_2185&63_509542f2185&0_2185&30_*8
    /*
    Make loop to go through the to_decrypt string by increments of the length_of_to_decrypt
    and check if can be divisible by formula when next to a letter, or if 
    */
}

int main() {
    int choice;
    std::string encryption_key;
    std::cout<<"Enter encryption key: ";
    std::cin>>encryption_key;
    std::cout<<"Enter 1 for encryption, 2 for decryption: ";
    std::cin>>choice;
    

    if(choice==1){
        std::cout<<"Enter what is to be encrypted: ";
        std::string to_decrypt;
        std::cin>>to_decrypt;
        std::cout<<encrypt_to_hex_decimal(to_decrypt,encryption_key)<<"\n";
        system("pause");
    }
    
}