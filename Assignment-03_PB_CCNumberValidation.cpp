#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

bool isvalidcc(const string& s) {
	int oddDigitSum = 0;
	int evenDigitSum = 0;
	
	if ( 13 < s.size() < 17) {


		//sum odd digits
		for (int i = s.size() - 2; i >= 0; i -= 2) {
			int num = int(s[i]) - 48;
			num = num * 2;
			if (num > 9) {
				int rhs = num % 10;
				int lhs = (num / 10) % 10;
				int result = rhs + lhs;
				oddDigitSum += result;
				//cout << result << " ";
			}
			if(num <= 9){
				oddDigitSum += num;
				//cout << num << " ";
			}
			
		}

		//sum even digits
		for (int i = s.size() - 1; i >= 0; i -= 2) {
			int num = int(s[i]) - 48;
			//num = num * 2;
			if (num > 9) {
				int rhs = num % 10;
				int lhs = (num / 10) % 10;
				int result = rhs + lhs;
				evenDigitSum += result;
				//cout << result << " ";
			}
			if (num <= 9) {
				evenDigitSum += num;
				//cout << num << " ";
			}
			
		} 
	}

	int totalSum = oddDigitSum + evenDigitSum;
	bool isDivisibleBy10 = (totalSum % 10) == 0;

	//cout << "|| " << oddDigitSum << " + " << evenDigitSum << " = " << totalSum << " ||";

	return isDivisibleBy10;
}

/*
	java code translation

public boolean isValidCC(String s) {
	
	if( s.size() > 13 && s.size < 17) {
		int sumOdd = 0;
		int sumEven = 0;

	
		//sum odd digits
		for(int i = s.size() - 1; i >= 0; i -= 2) {
			int num = s[i] * 2;
			if(num > 9) {
				int rhs = num % 10;
				int lhs = num % 10;
				int result  = rhs + lhs;

				sumOdd += result;
			}
			sumOdd += num;
		}

		//sum even digits 
		for(int i = s.size(); i >= 0; i -= 2) {
			int num = s[i] * 2;
			if(num > 9) {
				int rhs = num % 10;
				int lhs = num % 10;
				int result  = rhs + lhs;

				sumEven += result;
			}
			sumEven += num;
		}

		int totalSum = sumOdd + sumEven;

		boolean isValid = (totalSum % 10 == 0) ? true : false;

		return isValid
	}
}
*/

int evenDigit() {
	return 0;
}

int oddDigit() {
	return 0;
}

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}


