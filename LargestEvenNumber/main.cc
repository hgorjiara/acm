#include <iostream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int toInt(char c){
	return c-'0';
}

string firstEvenNumber(string str){
	int i = str.length()-1;
	while(i>=0){
		if(toInt(str[i])%2==0)
			break;
		i--;
	}
	if(i<0){
		return str;
	}
	char even = str[i];
	for(int j=i; j < str.length()-1; j++){
		str[j] = str[j+1];
	}
	str[str.length()-1] = even;
	return str;
}

string countingSort(string str){
	string sorted = str;
	int numberSize = 10;
	int index[numberSize];
	memset(index, 0, sizeof(index));
	for(int i=0; i<str.length(); i++){
		char c = str[i];
		index[toInt(c)]++;
	}
	for(int i=1; i< numberSize; i++){
		index[i] += index[i-1];
	}
	for(int i=0 ; i < str.length(); i++){
		int number = toInt(str[i]);
		sorted[--index[number]] = str[i];
	}
	reverse(sorted.begin(), sorted.end());
	return sorted;
}

string getLargestEvenNumber(string str){
	if(str.length() < 2){
		return str;
	}
	string sorted = countingSort(str);
	if(toInt(sorted[sorted.length()-1]) %2 == 0 ){
		return sorted;
	}
	sorted = firstEvenNumber(sorted);
	return sorted;
}

int main(){
	int n;
	cin >> n;
	string line;
	getline(cin, line);//getting rid of endl of the first line!
	while(getline(cin, line) && n > 0){
		cout << getLargestEvenNumber(line) << endl;
		n--;
	}
	 return 0;
}
