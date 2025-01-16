#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<char> encryption(vector<char> plain_text, int key) {
    vector<char> cipher_text;

    key = ((key % 26) + 26) % 26; 

    for (char ch : plain_text) {
        if (isalpha(ch)) { 
            char base = islower(ch) ? 'a' : 'A'; 
            char encrypted_char = (ch - base + key) % 26 + base; 
            cipher_text.push_back(encrypted_char);
        } else {
            cipher_text.push_back(ch);
        }
    }

    return cipher_text;
}

vector<char> decryption(vector<char> cipher_text, int key) {
    return encryption(cipher_text, -key);
}

int main() {
    string input;
    int key;

    cout << "Enter the plain text: ";
    getline(cin, input);

    vector<char> plain_text(input.begin(), input.end());

    cout << "Enter the key value (integer): ";
    cin >> key;

    vector<char> cipher_text = encryption(plain_text, key);

    cout << "Cipher text: ";
    for (char ch : cipher_text) {
        cout << ch;
    }
    cout << endl;

    vector<char> decrypted_text = decryption(cipher_text, key);

    cout << "Decrypted text: ";
    for (char ch : decrypted_text) {
        cout << ch;
    }
    cout << endl;

    return 0;
}
