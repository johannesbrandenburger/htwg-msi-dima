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

long long int pow_with_more_power(long long int base, long long int exponent)
{
    long long int output = 1;
    for (long long int i = 0; i < exponent; i++)
    {
        output *= base;
    }
    return output;
}

string get_code_from_number(long long int number, string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", long long int allowed_length = 5)
{
    string output = "";
    long long int alphabet_length = alphabet.length();
    for (long long int i = 0; i < allowed_length; i++)
    {
        output += (char)(alphabet[number % alphabet_length]);
        number /= alphabet_length;
    }
    return output;
}


string get_code_from_number_with_variable_length(
    long long int number,
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
    vector<long long int> allowed_lengthes = {5, 6, 7, 8, 9, 10})
{
    long long int different_lengthes = allowed_lengthes.size();
    
    // determine the length of the code and the number of the code in the length
    long long int length = 0;
    for (long long int i = 0; i < different_lengthes; i++)
    {
        long long int current_length_combinations = pow_with_more_power(alphabet.length(), allowed_lengthes[i]);
        if (number < current_length_combinations)
        {
            length = allowed_lengthes[i];
            break;
        }
        else
        {
            number -= current_length_combinations;
        }
    }

    return get_code_from_number(number, alphabet, length);
}


long long int count_combinations(string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int> allowed_lengthes = {5, 6, 7, 8, 9, 10})
{
    long long int output = 0;
    int different_lengthes = allowed_lengthes.size();
    for (long long int i = 0; i < different_lengthes; i++)
    {
        output += pow_with_more_power(alphabet.length(), allowed_lengthes[i]);
    }
    return output;
}

string try_crack_hash(
    string searched_hash,
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
    vector<long long int> allowed_lengthes = {5, 6, 7, 8, 9, 10},
    bool debug = false
    )
{
    long long int combinations = count_combinations(alphabet, allowed_lengthes);
    time_t start_time = time(0);
    unsigned char hash[SHA_DIGEST_LENGTH];
    string hash_string = "";

    for (long long int i = 0; i < combinations; i++)
    {
        string code = get_code_from_number_with_variable_length(i, alphabet, allowed_lengthes);
        
        // create the hash
        SHA1((unsigned char*)code.c_str(), code.length(), hash);
        hash_string = get_hex_representation(hash, SHA_DIGEST_LENGTH);
        
        if (debug)
        {
            cout << "try code: " << code << " hash: " << hash_string << " ==? " << searched_hash << endl;
        }

        // every 100000th try print the current code and the progress
        if (i % 100000 == 0)
        {

            // calculate progress
            float progress = ((float)i / (float)combinations);

            // calculate remaining minutes
            float remaining_minutes = (time(0) - start_time) / progress;
            remaining_minutes -= (time(0) - start_time);
            remaining_minutes /= 60;

            cout << "\r" << "current code: " << code << " | progress: " << (progress * 100) << "% | remaining minutes to test all combinations: " << remaining_minutes << "                    ";
            cout.flush();
        }

        if (searched_hash == hash_string)
        {

            // print out the minutes it took to crack the hash
            cout << endl << "took " << (time(0) - start_time) / 60 << "min to crack the hash" << endl;
            return code;
        }
    }
    return "";
}

void test_all_helper_functions() {
    assert(get_code_from_number(0) == "aaaaa");
    assert(get_code_from_number(1) == "baaaa");
    assert(get_code_from_number(count_combinations("abc", vector<long long int>{5}) - 1, "abc", 5) == "ccccc");
    assert(count_combinations("abc", vector<long long int>{1, 2, 3}) == 39);
    assert(get_code_from_number_with_variable_length(1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5}) == "baaaa");
    assert(get_code_from_number_with_variable_length(2, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5}) == "caaaa");
    assert(get_code_from_number_with_variable_length(0, "abc", vector<long long int>{1, 2, 3}) == "a");
    assert(get_code_from_number_with_variable_length(1, "abc", vector<long long int>{1, 2, 3}) == "b");
    assert(get_code_from_number_with_variable_length(2, "abc", vector<long long int>{1, 2, 3}) == "c");
    assert(get_code_from_number_with_variable_length(3, "abc", vector<long long int>{1, 2, 3}) == "aa");
    assert(get_code_from_number_with_variable_length(4, "abc", vector<long long int>{1, 2, 3}) == "ba");
    assert(get_code_from_number_with_variable_length(5, "abc", vector<long long int>{1, 2, 3}) == "ca");
    assert(get_code_from_number_with_variable_length(6, "abc", vector<long long int>{1, 2, 3}) == "ab");
    assert(get_code_from_number_with_variable_length(7, "abc", vector<long long int>{1, 2, 3}) == "bb");
    assert(get_code_from_number_with_variable_length(8, "abc", vector<long long int>{1, 2, 3}) == "cb");
    assert(get_code_from_number_with_variable_length(9, "abc", vector<long long int>{1, 2, 3}) == "ac");
    assert(get_code_from_number_with_variable_length(10, "abc", vector<long long int>{1, 2, 3}) == "bc");
    assert(get_code_from_number_with_variable_length(11, "abc", vector<long long int>{1, 2, 3}) == "cc");
    assert(get_code_from_number_with_variable_length(12, "abc", vector<long long int>{1, 2, 3}) == "aaa");
    assert(get_code_from_number_with_variable_length(13, "abc", vector<long long int>{1, 2, 3}) == "baa");

    // test the bruteforce function
    string searched_code = "ababc";
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)searched_code.c_str(), searched_code.length(), hash);
    string searched_hash = get_hex_representation(hash, SHA_DIGEST_LENGTH);
    string result = try_crack_hash(searched_hash, "abc", vector<long long int>{5}, false);
    assert(result == searched_code);
}


int main(int, const char **)
{
    test_all_helper_functions();

    cout << endl << "------------------- htwg-dima-task-2 -------------------" << endl;
    cout << "Possible combinations in System 1 (5 signs):    " << count_combinations("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5}) << endl;
    cout << "Possible combinations in System 2 (10 signs):   " << count_combinations("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{10}) << endl;
    cout << "Possible combinations in System 3 (5-10 signs): " << count_combinations("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5, 6, 7, 8, 9, 10}) << endl;

    // searched hash values
    string searched_hash_system_1 = "7738d1909d7dee18196f733d0d508d871d05cc80";
    string searched_hash_system_2 = "e39156538e3e7193fdf6356469fa7414d078f97e";
    string searched_hash_system_3 = "0a3bd07f4152f7f7a9655acfbeb8b4f08bc5861a";

    // crack system 0 (demo)
    // string searched_code = "msi0";
    // SHA1 checksum;
    // checksum.update(searched_code);
    // string searched_hash_system_0 = checksum.final();
    // cout << "try to crack demosystem (4 signs) with SHA-1: " << searched_hash_system_0 << endl;
    // string result_system_0 = try_crack_hash(searched_hash_system_0, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{4}, false);
    // cout << "result: " << result_system_0 << endl;

    // crack system 1
    cout << "try to crack system 1 (5 signs) with SHA-1: " << searched_hash_system_1 << endl;
    string result_system_1 = try_crack_hash(searched_hash_system_1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5}, false);
    cout << "result: " << result_system_1 << endl;

    // output:
    // ------------------- htwg-dima-task-2 -------------------
    // Possible combinations in System 1 (5 signs):    916132832
    // Possible combinations in System 2 (10 signs):   839299365868340224
    // Possible combinations in System 3 (5-10 signs): 853058371851163296
    // try to crack system 1 (5 signs) with SHA-1: 7738d1909d7dee18196f733d0d508d871d05cc80
    // current code: WmI42 | progress: 88.5679% | remaining minutes: 7.273
    // result: MsI42
    // took 30min approx.↑


    // crack system 2
    // cout << "try to crack system 2 (10 signs) with SHA-1: " << searched_hash_system_2 << endl;
    // string result_system_2 = try_crack_hash(searched_hash_system_2, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{10}, false);
    // cout << "result: " << result_system_2 << endl;

    // crack system 3
    // cout << "try to crack system 3 (5-10 signs) with SHA-1: " << searched_hash_system_3 << endl;
    // string result_system_3 = try_crack_hash(searched_hash_system_3, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", vector<long long int>{5, 6, 7, 8, 9, 10}, false);
    // cout << "result: " << result_system_3 << endl;


    return 0;
}