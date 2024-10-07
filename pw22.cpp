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
#include  <bits/stdc++.h>

//TODO 1.Make get_key symbol (/ utt.) conversion to decimal
//TODO 3.Add function to customize operations with to_encrypt/to_decrypt (Save operations in a list in a seperate file)
std::string replace_equal_digits(int keyd_,int last_int_of_key_,std::string symbol){//makes a function for equal ints in the encrypted string to be replaced by a symbol
    std::string keyd_string = std::to_string(keyd_);//converts one encrypted hexadeciaml part of the whole encrypted string to a stringstd::string symbol = "@";
    std::stringstream new_replaced_symbol_stringstream;//creates a new stringstream in which to replace the ints in 
    char last_int_of_key = last_int_of_key_ + '0';//converts the last_int_of_key to a char data type
    for(char c:keyd_string){//loops over each character in the keyd string
        if(isdigit(c)&&c==last_int_of_key){//checks if the character represents an int and if it is equal to the last int of the converted key
            new_replaced_symbol_stringstream<<symbol;//adds a string symbol to the stringsream
        }
        else{//if the character is not equal to the last int of the converted key
            new_replaced_symbol_stringstream<<c;//adds the same value to the stringstream
        }
    }
    std::string new_replaced_symbol_string = new_replaced_symbol_stringstream.str();//converts the stringstream to a string
    return new_replaced_symbol_string;//returns the new string
}

std::string hexToAscii(std::string c)
{
	int length = c.length();
	std::string newString;
	for (int i = 0; i < length; i+=2)
	{
		std::string byte = c.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}
	return newString;
}



std::string replace_equal_symbols(int last_int_of_key, std::string encrypted_txt,std::string symbol){//sets up a function to change the symbols in the to_decrypt string back to the last int of the key
    std::stringstream replaced_to_decrypt;//sets up a stringstream for the replaced symbols
    char s = symbol[0];
    for(char c:encrypted_txt){//loops through the characters of the encrypted text
        if(c==s){//checks if the character is a symbol
            replaced_to_decrypt<<last_int_of_key;//adds the last int of the key to the stringstream
        }
        else{
            replaced_to_decrypt<<c;//the rest of the characters get added back
        }
    }
    std::string replaced_to_decrypt_string = replaced_to_decrypt.str();//converts the stringstream to a string
    return replaced_to_decrypt_string;//returns the newly replaced symbols string
}
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
        else if(isdigit(c)&&c!=last_int_of_key_1){
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
std::string encrypt_to_hex_decimal(std::string to_encrypt, std::string key,std::string symbol){//main function to encrypt the "to_decrypt" text with the "key" as the key
    std::stringstream end_string;//sets up a stringstream in which all of the encrypted parts of the text will be inserted into
    std::stringstream converted_to_hex;//sets up a seperate stringstream in which all of the characters of the original string will be converted to hex
    
    
    /*
    int og_size = to_encrypt.length();//saves the size of the og string to be used later in decryption
    */
    for(char character:to_encrypt){//loops over the characters in the original string
        converted_to_hex<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<int>(static_cast<unsigned char>(character));//formats a hex value of a max length of 2 with the filler being 0 and first casts character to unsigned char and then to an int
    }
    to_encrypt = converted_to_hex.str();//replaces the original "to_decrypt" string with the newly converted hex string
    
    std::pair<int,int> gotten_keys = get_key(key);
    int last_int_of_key = gotten_keys.first;
    int key_for_use = gotten_keys.second;
    //converts the character in char_list into an int
    int extra_encr = 1;
    if(to_encrypt.length()>1){
        for(int i = 0;i<to_encrypt.length()*2-1;i++){
            if(i<to_encrypt.size()-1){
                if(isdigit(to_encrypt[i])){
                    if(isdigit(to_encrypt[i+1])){
                        int num_1 = (to_encrypt[i] - '0') * key_for_use;
                        int num_2 =  (to_encrypt[i + 1] - '0') * (i+1);
                        end_string<<num_1<<"&"<<num_2<<"_";
                        i++;
                    }
                    if(isalpha(to_encrypt[i+1])){
                        if(key_for_use%2==0){
                            extra_encr = 3;
                        }
                        else{
                            extra_encr = 2;
                        }
                        int keyd = (to_encrypt[i] - '0')*key_for_use;
                        keyd = keyd *extra_encr;
                        keyd = keyd *(i+extra_encr);
                        std::string keyd_gone_over = replace_equal_digits(keyd,last_int_of_key,symbol);
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


int return_length_of_decryptable_string(std::string to_decrypt){
    
    int length_of_to_decrypt_string_stringstream = 0;
    for(int i = 0;i<to_decrypt.length();i++){

        if(to_decrypt[i]=='*'){
            break;
        }
        length_of_to_decrypt_string_stringstream+=1;
    }
    
    return length_of_to_decrypt_string_stringstream;
}


std::string decrypt(std::string to_decrypt,std::string key,std::string symbol){
    std::pair<int,int> gotten_keys = get_key(key);
    int last_int_of_key = gotten_keys.first;
    int key_for_use = gotten_keys.second;
    to_decrypt = replace_equal_symbols(last_int_of_key,to_decrypt,symbol);
    int length_of_to_decrypt = return_length_of_decryptable_string(to_decrypt);
    std::stringstream end_string;
    std::stringstream d_encr;
    int k = 0,j,extra_decr = 0;
    if(length_of_to_decrypt>1){
        for(int i = 0;i<length_of_to_decrypt+1;i++){
            if(i<to_decrypt.size()-1){
                
                if(isdigit(to_decrypt[i])){
                    d_encr<<to_decrypt[i];
                }
                else if(to_decrypt[i] == symbol[0]){
                    d_encr<<last_int_of_key; 
                }
                else if(isalpha(to_decrypt[i])){
                    std::string int_char_encr = d_encr.str();
                    int int_char_decr = std::stoi(int_char_encr);
                    if(key_for_use%2==0){
                        extra_decr = 3;
                    }
                    else{
                        extra_decr = 2;
                    }
                    int_char_decr=int_char_decr/(k+extra_decr)/key_for_use/extra_decr;
                    end_string<<int_char_decr<<to_decrypt[i];
                    d_encr.str("");
                    d_encr.clear();
                    k+=2;
                }
                else if(to_decrypt[i]=='&'){
                    
                    std::string int_int_1_encr = d_encr.str();
                    int int_int_1_decr = std::stoi(int_int_1_encr);
                    int_int_1_decr = int_int_1_decr/key_for_use;
                    end_string<<int_int_1_decr;
                    d_encr.str("");
                    d_encr.clear();
                    k+=1;
                }
                else if(to_decrypt[i]=='_'){
                    
                    std::string int_int_2_encr = d_encr.str();
                    int int_int_2_decr = std::stoi(int_int_2_encr);
                    int_int_2_decr = int_int_2_decr/k;
                    end_string<<int_int_2_decr;
                    d_encr.str("");
                    d_encr.clear();
                    k+=1;
                }
                    
            }
        }
    }
    
    
    return hexToAscii(end_string.str());
    
}


enum class Command {
    Commands,
    Encrypt,
    Decrypt,
    Copy,
    Exit,
    Unknown
};

Command getCommand(const std::string& input) {
    if (input == "decrypt") return Command::Decrypt;
    if (input == "exit") return Command::Exit;
    if (input == "copy") return Command::Copy;
    if (input == "Commands") return Command::Commands;
    if (input == "encrypt") return Command::Encrypt;  
    return Command::Unknown;
}

void copyToClipboard(const std::string& text){
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE,text.size()+1);
    if(!hg){
        EmptyClipboard();
        std::cout<<("Error: Clipboard error");
        return;
    }
    memcpy(GlobalLock(hg),text.c_str(),text.size()+1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT,hg);
    CloseClipboard();
    GlobalFree(hg);
}

int main() {
    std::string encryption_key,symbol,input,last_output,to_encrypt,to_decrypt;
    
    while (true) {
        std::cout << "Enter command (Commands for all): ";
        std::cin>>input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (getCommand(input)) {
            case Command::Exit:
                return 0;
            case Command::Commands:{
                std::cout << "Enter: \n'encrypt' to encrypt,\n'copy' to copy last output,\n'decrypt' to decrypt,\n'exit' to quit,\n ";
                break;
            }
            case Command::Copy:
                if (!last_output.empty()) {
                    copyToClipboard(last_output);
                    std::cout << "Last output copied to clipboard: " << last_output << std::endl;
                } else {
                    std::cout << "No previous output to copy!" << std::endl;
                }
                break;

            case Command::Encrypt:
                std::cout<<"Enter what is to be encrypted: ";
                std::getline(std::cin,to_encrypt);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Enter key for encryption: ";
                std::cin>>encryption_key;
                std::cout<<"Enter symbol for encryption: ";
                std::cin>>symbol;
                last_output = encrypt_to_hex_decimal(to_encrypt, encryption_key,symbol);
                std::cout << "Encrypted output: " << last_output << std::endl;
                break;

            case Command::Decrypt:
                std::cout<<"Enter what is to be decrypted: ";
                std::getline(std::cin,to_decrypt);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Enter key for decryption: ";
                std::cin>>encryption_key;
                std::cout<<"Enter symbol for decryption: ";
                std::cin>>symbol;
                last_output = decrypt(to_decrypt, encryption_key,symbol);
                std::cout << "Decrypted output: " << last_output << std::endl;
                break;

            default:
                std::cout << "Unknown command. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}