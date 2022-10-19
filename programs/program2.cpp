#include <bits/stdc++.h>
using namespace std;
// Transposition Cipher

int key;

string inputText, cipherText;
// string helper = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
string helper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string removeSpaces(string input) {
    int n = input.length() - 1;
    string temp;
    for (int i = 0; i <= n; i++)
        if (isalpha(input[i]))
            temp.push_back(input[i]);
    return temp;
}

void encrypt(string &input, int key) {              
    int k = 0, j, i, l = 0;
    int n = input.length() - 1;
    char matrix[50][key];

    for (i = 0; i <= (n / key); i++){
        for (j = 0; j < key; j++) {
            if (k == n+1)                   // last unfilled spaces in the rectangular matrix
                matrix[i][j] = helper[l++];
            else
                matrix[i][j] = input[k++];
        }
    }

    cout<<"\nMatrix: "<<endl;
    for (i = 0; i <= (n / key); i++){
        for (j = 0; j < key; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    input.clear();                              // formal parameters so passed have fixed value of size, so to accomodate extra filled letters, it is necessary to clear and push back
    for (i = 0; i < key; i++){
        for (j = 0; j <= (n / key); j++)
            input.push_back(matrix[j][i]);
    }
}

void decrypt(string &cipher, int key) {
    int k = 0, j, i;
    int n = cipher.length() - 1;
    char matrix[50][key];

    for (i = 0; i < key; i++) {
        for (j = 0; j <= (n / key); j++)
            matrix[j][i] = cipher[k++];
    }

    cout<<"\nMatrix: "<<endl;
    for (i = 0; i <= (n / key); i++) {
        for (j = 0; j < key; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    cipher.clear();
    for (i = 0; i <= (n / key); i++) {
        for (j = 0; j < key; j++)
            cipher.push_back(matrix[i][j]);
    }
}

int main() {
    cout<<"\nFAIZAN CHOUDHARY\n20BCS021\n";
    cout<<"\nTranposition Cipher\n";
    char ch;
    int c;
    while (true) {
        cout<<"\nMENU:\n1. Encrpyt text.\n2. Decrypt text.\n3. Exit.\n";
        cin>>c;
        cin.get();
        switch(c) {
            case 1: cout<<"\nEnter input plain text to be encrypted (without special characters): ";
                    getline(cin, inputText);
                    inputText = removeSpaces(inputText);
                    cout<<"\nEnter key for encryption: ";
                    cin>>key;
                    encrypt(inputText, key);
                    cout<<"\nEncrypted text: "<<inputText<<endl;
                    break;
            case 2: cout<<"\nEnter input plain text to be decrypted (without special characters): ";
                    getline(cin, cipherText);
                    cipherText = removeSpaces(cipherText);
                    cout<<"\nEnter key for decryption: ";
                    cin>>key;
                    decrypt(cipherText, key);
                    cout<<"\nDecrypted text: "<<cipherText<<endl;
                    break;
            case 3: exit(0);
            default: cout<<"\nWrong choice! Enter again...\n";
        }
    }
    return 0;
}