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

int main(){
    std::stringstream converted_to_hex;
    std::string to_encrypt = "JBAPW_PR";
    for(char character:to_encrypt){//loops over the characters in the original string
        converted_to_hex<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<int>(static_cast<unsigned char>(character));//formats a hex value of a max length of 2 with the filler being 0 and first casts character to unsigned char and then to an int
    }
    std::string result = converted_to_hex.str();
    std::cout<<result<<"\n"<<result.size()/2;
}