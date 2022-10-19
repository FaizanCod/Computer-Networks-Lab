#include <bits/stdc++.h>
using namespace std;

// char mapLowercase[27];
// char mapUppercase[27];
unordered_map<char, int> mapLowercase;
unordered_map<char, int> mapUppercase;

void mapper() {
    // mapLowercase[0] = '0';
    // mapUppercase[0] = '0';
    for (int i=0; i<26; i++) {
        // mapLowercase[i+1] = 'a' + i;
        // mapUppercase[i+1] = 'A' + i;
        mapLowercase.insert({'a' + i, i});          // i+1 for a=1
        mapUppercase.insert({'A' + i, i});
    }
    // for (int i=0; i<27; i++)
    //     cout<<i<<": "<<mapLowercase[i]<<endl;
    // for (auto x: mapLowercase)
    //     cout<<x.first<<" : "<<x.second<<endl;
}

void encrypt(string &input, int key) {
    int n = input.length() - 1;
    for (int i=0; i<=n; i++) {
        if (input[i] == ' ') 
            input[i] = ' ';
        else if (mapLowercase.find(input[i]) != mapLowercase.end())
            // cout<<(mapLowercase.find(input[i])->second + key) % 26;
            input[i] = ((mapLowercase.find(input[i])->second + key) % 26) + 'a';
        else if (mapUppercase.find(input[i]) != mapUppercase.end())
            input[i] = ((mapUppercase.find(input[i])->second + key) % 26) + 'A';

        // cout<<input[i];
    }
}

void decrypt(string &input, int key) {
    int n = input.length() - 1;
    for (int i=0; i<=n; i++) {
        if (input[i] == ' ') 
            input[i] = ' ';
        else if (mapLowercase.find(input[i]) != mapLowercase.end())
            // cout<<(mapLowercase.find(input[i])->second + key) % 26;
            input[i] = ((mapLowercase.find(input[i])->second - key + 26) % 26) + 'a';           // + 26 for negative index checking, - key for going backwards
        else if (mapUppercase.find(input[i]) != mapUppercase.end())
            input[i] = ((mapUppercase.find(input[i])->second - key + 26) % 26) + 'A';

        // cout<<input[i];
    }
}

int main() {
    cout<<"\nFAIZAN CHOUDHARY\n20BCS021\n";
    cout<<"\nSubstitution Cipher\n";
    mapper();
    int key;
    string inputText, cipherText;
    char ch;
    int c;
    while (true) {
        cout<<"\nMENU:\n1. Encrpyt text.\n2. Decrypt text.\n3. Exit.\n";
        cin>>c;
        cin.get();
        switch(c) {
            case 1: cout<<"\nEnter input plain text to be encrypted (without special characters): ";
                    getline(cin, inputText);
                    cout<<"\nEnter key for encryption: ";
                    cin>>key;
                    encrypt(inputText, key);
                    cout<<inputText<<endl;
                    break;
            case 2: cout<<"\nEnter input plain text to be decrypted (without special characters): ";
                    getline(cin, cipherText);
                    cout<<"\nEnter key for decryption: ";
                    cin>>key;
                    decrypt(cipherText, key);
                    cout<<cipherText<<endl;
                    break;
            case 3: exit(0);
            default: cout<<"\nWrong choice! Enter again...\n";
        }
    }
    return 0;
}