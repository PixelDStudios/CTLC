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

std::string replace_equal_symbols(int last_int_of_key, std::string encrypted_txt){//sets up a function to change the symbols in the to_encrypt string back to the last int of the key
    std::stringstream replaced_to_encrypt;//sets up a stringstream for the replaced symbols
    for(char c:encrypted_txt){//loops through the characters of the encrypted text
        if(c=='@'){//checks if the character is a symbol
            replaced_to_encrypt<<last_int_of_key;//adds the last int of the key to the stringstream
        }
        else{
            replaced_to_encrypt<<c;//the rest of the characters get added back
        }
    }
    std::string replaced_to_encrypt_string = replaced_to_encrypt.str();//converts the stringstream to a string
    return replaced_to_encrypt_string;//returns the newly replaced symbols string
}
std::pair<int,int> get_key(std::string key){//sets up a function 
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
        if(isdigit(c)){
            converted_key<<c;
        }
    }
    std::string acquired_key = converted_key.str();
    int last_int_of_key = acquired_key[acquired_key.size()-1] - '0';
    int key_for_use = std::stoi(acquired_key);
    return std::make_pair(last_int_of_key,key_for_use);
}
std::string encrypt_to_hex_decimal(std::string to_encrypt, std::string key){//main function to encrypt the "to_encrypt" text with the "key" as the key
    std::stringstream end_string;//sets up a stringstream in which all of the encrypted parts of the text will be inserted into
    std::stringstream converted_to_hex;//sets up a seperate stringstream in which all of the characters of the original string will be converted to hex
    
    
    
    int og_size = to_encrypt.length();//saves the size of the og string to be used later in decryption
    
    for(char character:to_encrypt){//loops over the characters in the original string
        converted_to_hex<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<int>(static_cast<unsigned char>(character));//formats a hex value of a max length of 2 with the filler being 0 and first casts character to unsigned char and then to an int
    }
    to_encrypt = converted_to_hex.str();//replaces the original "to_encrypt" string with the newly converted hex string
    
    std::pair<int,int> gotten_keys = get_key(key);
    int last_int_of_key = gotten_keys.first;
    int key_for_use = gotten_keys.second;
    //converts the character in char_list into an int
    int extra_encr = 1;
    if(og_size>1){
        for(int i = 0;i<og_size-1;i++){
            if(i<to_encrypt.size()-1){
                if(isdigit(to_encrypt[i])){
                    if(isdigit(to_encrypt[i+1])){
                        int num_1 = (to_encrypt[i] - '0') * 10 + (to_encrypt[i + 1] - '0');
                        num_1 = num_1  * (i+1) ;
                        end_string<<num_1<<"_";
                        i++;
                    }
                    if(isalpha(to_encrypt[i+1])){
                        if(key_for_use%2==0){
                            extra_encr = 3;
                        }
                        else{
                            extra_encr = 2;
                        }
                        int keyd = to_encrypt[i]*key_for_use*extra_encr*(i+1);
                        
                        std::string keyd_gone_over = replace_equal_digits(keyd,last_int_of_key);
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
    end_string<<"*"<<og_size;
    
    std::string final_result = end_string.str();
    
    return final_result;
}


int return_length_of_decryptable_string(std::string to_decrypt){
    
    std::stringstream length_of_to_decrypt_string_stringstream;
    for(int i = 0;i<to_decrypt.length();i++){
        if(to_decrypt[i]=='*'){
            for(int j = i+1;j<to_decrypt.length();j++){
                length_of_to_decrypt_string_stringstream<<to_decrypt[j];
            }
            break;
        }
    }
    std::string length_of_to_decrypt_string_stringstream_string = length_of_to_decrypt_string_stringstream.str();
    int length_of_to_decrypt_string= std::stoi(length_of_to_decrypt_string_stringstream_string);
    return length_of_to_decrypt_string;
}


std::string decrypt(std::string to_decrypt,std::string key){
    std::pair<int,int> gotten_keys = get_key(key);
    int last_int_of_key = gotten_keys.first;
    int key_for_use = gotten_keys.second;
    to_decrypt = replace_equal_symbols(last_int_of_key,to_decrypt);
    int length_of_to_decrypt = return_length_of_decryptable_string(to_decrypt);
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
        std::string to_encrypt;
        std::cin>>to_encrypt;
        std::cout<<encrypt_to_hex_decimal(to_encrypt,encryption_key)<<"\n";
        system("pause");
    }
    
}

