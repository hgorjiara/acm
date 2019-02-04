#include <iostream>
using namespace std;
/**
Examples:
4 = 0 + 1 * 2 * 2
5 = 0 + 1 * 2 * 2 + 1
6 = 0 + 1 + 1 + 1 * 2

*/

int minimumOperation(int number){
	if(number == 0){
		return 0;
	}
	int min = 0;
	if( number % 2 == 0){
		min = minimumOperation(number/2);
	}
	int one = minimumOperation(number - 1);
	if ( one < min){
		min = one;
	}
	return min + 1; 
}

int minimumOperationDP(int number){
	int mins [ number + 1];
	mins[0] = 0;
	for (int i=1; i < number+1; i++){
		int minimum = mins[i-1];
		if(i %2 == 0 && minimum > mins[i/2]) {
			minimum = mins[i/2];
		}
		mins[i] = ++minimum;
	}
	return mins[number];
}

int main(){
	int n, number;
	cin >> n;
	while ( n > 0){
		cin >> number;
		cout << minimumOperationDP(number) << endl;
		n--;
	}

}
