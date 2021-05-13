#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Card
{
public:
	Card(int suit, int number)
	{
		this->suit = suit;
		this->number = number;
	}

	void print()
	{
		vector<string> numbers = { "0","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
		//vector<string> suits = { "♠", "♥", "♦", "♣" };
		vector<string> suits = { "a", "b", "c", "d" };
		cout << suits[suit] << numbers[number];
	}
	int suit;
	int number;
};