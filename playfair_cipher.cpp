#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Function to prepare the Playfair cipher matrix
void createMatrix(const string &key, vector<vector<char>> &matrix) {
    unordered_set<char> used;
    string preparedKey = "";

    // Prepare the key by removing duplicates and ignoring 'J'
    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Treat 'I' and 'J' as the same
        if (used.find(c) == used.end() && isalpha(c)) {
            preparedKey += c;
            used.insert(c);
        }
    }

    // Fill the matrix with the key
    int index = 0;
    for (char c : preparedKey) {
        matrix[index / 5][index % 5] = c;
        index++;
    }

    // Fill the rest of the matrix with remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; // Skip 'J'
        if (used.find(c) == used.end()) {
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }
}

// Function to display the matrix
void showMatrix(const vector<vector<char>> &matrix) {
    cout << "\nPlayfair Cipher Matrix:\n";
    for (const auto &row : matrix) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}

// Function to format the input text for encryption/decryption
string formatText(string text) {
    string formatted = "";
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Treat 'I' and 'J' as the same
        if (isalpha(c)) {
            formatted += c;
        }
    }

    // Insert 'X' between duplicate letters and ensure even length
    for (size_t i = 0; i < formatted.length() - 1; i += 2) {
        if (formatted[i] == formatted[i + 1]) {
            formatted.insert(i + 1, "X");
        }
    }
    if (formatted.length() % 2 != 0) {
        formatted += 'X';
    }
    return formatted;
}

// Function to find the position of a character in the matrix
void findPosition(const vector<vector<char>> &matrix, char c, int &row, int &col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to encrypt/decrypt a pair of characters
string processPair(const vector<vector<char>> &matrix, char a, char b, bool encrypt) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    if (row1 == row2) {
        // Same row: shift columns
        col1 = (col1 + (encrypt ? 1 : 4)) % 5;
        col2 = (col2 + (encrypt ? 1 : 4)) % 5;
    } else if (col1 == col2) {
        // Same column: shift rows
        row1 = (row1 + (encrypt ? 1 : 4)) % 5;
        row2 = (row2 + (encrypt ? 1 : 4)) % 5;
    } else {
        // Rectangle swap
        swap(col1, col2);
    }

    return string(1, matrix[row1][col1]) + string(1, matrix[row2][col2]);
}

// Function to encrypt/decrypt text
string processText(const vector<vector<char>> &matrix, const string &text, bool encrypt) {
    string result = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        result += processPair(matrix, text[i], text[i + 1], encrypt);
    }
    return result;
}

int main() {
    string key, text;
    cout << "Enter the key for the Playfair Cipher: ";
    getline(cin, key);

    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    vector<vector<char>> matrix(5, vector<char>(5));
    
    createMatrix(key, matrix);
    showMatrix(matrix);

    string formattedText = formatText(text);
    cout << "\nFormatted Text: " << formattedText << endl;

    string encryptedText = processText(matrix, formattedText, true);
    cout << "\nEncrypted Text: " << encryptedText << endl;

    string decryptedText = processText(matrix, encryptedText, false);
    cout << "\nDecrypted Text: " << decryptedText << endl;

    return 0;
}
