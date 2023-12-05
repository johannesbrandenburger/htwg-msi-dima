#include <openssl/sha.h>
#include <string>
#include <array>
#include <iostream>
#include <assert.h>
#include <list>
#include <vector>
#include <cmath>
using namespace std;


string get_hex_representation(const unsigned char *Bytes, size_t Length) {
    string ret(Length*2, '\0');
    const char *digits = "0123456789abcdef";
    for(size_t i = 0; i < Length; ++i) {
        ret[i*2]   = digits[(Bytes[i]>>4) & 0xf];
        ret[i*2+1] = digits[ Bytes[i]     & 0xf];
    }
    return ret;
}

int main() {

    string searched_hash_system_1 = "7738d1909d7dee18196f733d0d508d871d05cc80";

    time_t start_time = time(0);
    unsigned char hash[SHA_DIGEST_LENGTH];
    string hash_string = "";
    string code = "";

    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    long long int alphabet_length = alphabet.length();

    for (int x1 = 0; x1 < alphabet_length; x1++)
    {
        for (int x2 = 0; x2 < alphabet_length; x2++)
        {
            for (int x3 = 0; x3 < alphabet_length; x3++)
            {
                for (int x4 = 0; x4 < alphabet_length; x4++)
                {
                    for (int x5 = 0; x5 < alphabet_length; x5++)
                    {
                        code = "";
                        code += alphabet[x1];
                        code += alphabet[x2];
                        code += alphabet[x3];
                        code += alphabet[x4];
                        code += alphabet[x5];
                        SHA1((unsigned char*)code.c_str(), code.length(), hash);
                        hash_string = get_hex_representation(hash, SHA_DIGEST_LENGTH);
                        // cout << code << " " << hash_string << endl;
                        if (hash_string == searched_hash_system_1)
                        {
                            cout << "Found code: " << code << endl;
                            cout << "Time elapsed: " << time(0) - start_time << " seconds" << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

