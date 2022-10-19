#include <bits/stdc++.h>
using namespace std;

string inputText, cipherText, helper;
// string helper = "computernetworkslaboratoryisfunandexcitingforallcomputersciencestudentsinjamiamilliaislamianewdelhicomputernetworkslaboratoryisfunandexcitingforallcomputersciencestudentsinjamiamilliaislamianewdelhi";
vector<string> cipherTable = {
    "aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", 
    "aabab", "aabba", "aabbb", "abaaa", "abaab", 
    "ababa", "ababb", "abbaa", "abbab", "abbba",
    "abbbb", "baaaa", "baaab", "baaba", "baabb",
    "babaa", "babab", "babba", "babbb", "bbaaa", "bbaab"
};

vector<char> decipherTable = {
    'a', 'b', 'c', 'd', 'e',
    'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
};

void convertLower(string s) {
    for (int i=0; i<s.length(); i++) {
        if (isupper(s[i]))
            s[i] += 32;
    }
}

string removeSpecial(string input) {
    int n = input.length() - 1;
    string temp;
    for (int i = 0; i <= n; i++) {
        if (isalpha(input[i]) || input[i] == ' ')
            temp.push_back(input[i]);
    }
    return temp;
}

string removeSpaces(string input) {
    int n = input.length() - 1;
    string temp;
    for (int i = 0; i <= n; i++)
        if (isalpha(input[i]))
            temp.push_back(input[i]);
    return temp;
}

void encrypt(string &input) {
    int n = input.length() - 1;
    string temp;
    for (int i=0; i<=n; i++) {
        if (input[i] >= 'a' && input[i] <= 'z')
            temp += (cipherTable[input[i]-'a']);
        else if (input[i] >= 'A' && input[i] <= 'Z')
            temp += (cipherTable[input[i]-'A']);
    }
    cout<<temp<<endl;
    int j = 0;
    input.erase();
    for (int i=0; i<temp.length(); i++) {
        if (temp[i] == 'a') {
            if (helper[j] == ' ') {
                input += ' ';
                i--;
                j++;
            }
            else
                input += tolower(helper[j++]);
        }
        else {
            if (helper[j] == ' ') {
                input += ' ';
                i--;
                j++;
            }
            else
                input += toupper(helper[j++]);
        }
    }
}

void decrypt(string &cipher) {
    int n = cipher.length() - 1;
    string temp;
    for (int i=0; i<=n; i++) {
        if (cipher[i] == ' ')
            temp += ' ';
        if (islower(cipher[i]))
            temp += 'a';
        else if (isupper(cipher[i]))
            temp += 'b';
    }
    // cout<<temp<<endl;
    cipher.erase();
    for (int i=0; i<temp.length(); i+=5) {
        string s;
        for (int j=0; j<5; j++) {
            if (temp[i+j] != ' ')
                s += temp[i+j];
            else {
                cipher += ' ';
                i++;
                j--;
            }
        }
        auto it = find(cipherTable.begin(), cipherTable.end(), s);
        if (it != cipherTable.end())
            cipher += decipherTable[it-cipherTable.begin()];
    }
}

int main() {
    cout<<"\nFAIZAN CHOUDHARY\n20BCS021\n";
    cout<<"\nBaconian Cipher\n";
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
                    cout<<"\nEnter sentence for encryption (should have atleast 5 times the size of input string): ";
                    getline(cin, helper);
                    convertLower(helper);
                    encrypt(inputText);
                    cout<<"\nEncrypted text: "<<inputText<<endl;
                    break;
            case 2: A:
                    cout<<"\nEnter input plain text to be decrypted (without special characters): ";
                    getline(cin, cipherText);
                    cipherText = removeSpaces(cipherText);
                    if (cipherText.length() % 5 != 0) {
                        cout<<"\nInvalid input! Length of string must be a multiple of 5. Enter again!\n";
                        goto A;
                    }
                    decrypt(cipherText);
                    cout<<"\nDecrypted text: "<<cipherText<<endl;
                    break;
            case 3: exit(0);
            default: cout<<"\nWrong choice! Enter again...\n";
        }
    }
    return 0;
}