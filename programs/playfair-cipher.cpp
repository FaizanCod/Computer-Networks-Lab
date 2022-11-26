#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

string key;
string inputText, cipherText;
vector<vector<char>> mat(5, vector<char>(5));

pii check(vector<vector<char>> &v, char ch){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(v[i][j]==ch)
				return {i,j};
		}
	}
}

string removeSpaces(string input) {
    int n = input.length() - 1;
    string temp;
    for (int i = 0; i <= n; i++)
        if (isalpha(input[i]))
            temp.push_back(input[i]);
    return temp;
}

void convertLower(string &s) {
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

string encrypt(string s) {
    string s1;
    for(auto it: s){
		if(it!=' ')
			s1.push_back(it);
	}
    for(int i=0;i<key.length();i++){
		if(key[i]=='j')
			key[i]='i';
	}
	int row=0;
	int col=0;
	set<char> st;

	for(int i=0;i<key.length();i++){

		if(st.find(key[i])==st.end()){

			if(col==5){
				row+=1;
				col=0;
				mat[row][col]=key[i];
				col++;
			}
			else{
				mat[row][col]=key[i];
				col++;
			}
			st.insert(key[i]);
		}
	}

	for(char ch='a';ch<='z';ch++){

		if(st.find(ch)==st.end() && ch!='j'){
			
			if(col==5){
				row+=1;
				col=0;
				mat[row][col]=ch;
				col++;
			} 
			else{
				mat[row][col]=ch;
				col++;
			}
			st.insert(ch);	
		}
	}
    cout<<"\nPlayFair Matrix:\n";
	for(auto it: mat){
		for(auto itt: it)
			cout<<itt<<" ";
		cout<<endl;
	}

	if(s1.length()%2)
		s1.push_back('x');

	string orig=s1;
	string enc;

	for(int i=0;i<s1.length();i+=2){
		
		if(s1[i]==s1[i+1])
			s1[i+1]='x';

		pii p1=check(mat,s1[i]);
		pii p2= check(mat,s1[i+1]);

		if(p1.first ==p2.first){
			enc.push_back(mat[p1.first][((p1.second+1)%5)]);
			enc.push_back(mat[p2.first][((p2.second+1)%5)]);
		}
		else if(p1.second==p2.second){
			enc.push_back(mat[(p1.first+1)%5][p1.second]);
			enc.push_back(mat[(p2.first+1)%5][p2.second]);
		}
		else{
			enc.push_back(mat[p1.first][p2.second]);
			enc.push_back(mat[p2.first][p1.second]);
		}
	}
    // cout<<enc<<endl;
    return enc;
}

string decrypt(string enc) {
    string dec;
	for(int i=0;i<enc.length();i+=2)
	{
		pii p1=check(mat,enc[i]);
		pii p2=check(mat,enc[i+1]);
		if(p1.first == p2.first)
		{
			dec.push_back(mat[p1.first][((p1.second-1+5)%5)]);
			dec.push_back(mat[p2.first][((p2.second-1+5)%5)]);
		}
		else if(p1.second==p2.second)
		{
			dec.push_back(mat[(p1.first-1+5)%5][p1.second]);
			dec.push_back(mat[(p2.first-1+5)%5][p2.second]);
		}
		else
		{
			dec.push_back(mat[p1.first][p2.second]);
			dec.push_back(mat[p2.first][p1.second]);
		}
	}
	// cout<<dec<<endl;
    return dec;
}

int main() {
    cout<<"\nFAIZAN CHOUDHARY\n20BCS021\n";
    cout<<"\nPlayfair Cipher\n";

    char ch;
    int c;
    while (true) {
        cout<<"\nMENU:\n1. Encrpyt text.\n2. Decrypt text.\n3. Exit.\n";
        cin>>c;
        cin.get();
        switch(c) {
            case 1: cout<<"\nEnter input plain text to be encrypted (without special characters): ";
                    getline(cin, inputText);
                    convertLower(inputText);
                    inputText = removeSpaces(inputText);
                    cout<<"\nEnter key for encryption: ";
                    getline(cin, key);
                    convertLower(key);
                    inputText = encrypt(inputText);
                    cout<<"\nEncrypted text: "<<inputText<<endl;
                    break;
            case 2: cout<<"\nEnter input plain text to be decrypted (without special characters): ";
                    getline(cin, cipherText);
                    cipherText = removeSpaces(cipherText);
                    cout<<"\nEnter key for decryption: ";
                    getline(cin, key);
                    convertLower(key);
                    cipherText = decrypt(cipherText);
                    cout<<"\nDecrypted text: "<<cipherText<<endl;
                    break;
            case 3: exit(0);
            default: cout<<"\nWrong choice! Enter again...\n";
        }
    }
    return 0;
}
