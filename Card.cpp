#ifndef CARD_CPP
#define CARD_CPP
#include <iostream>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
using namespace std;

class Card
{
public:
	int suit;
	int number;
	Card(int suit, int number)
	{
		this->suit = suit;
		this->number = number;
	}

	void printSuit(int suitToSelect) 
	{
		_setmode(_fileno(stdout), _O_U16TEXT);//改輸出編碼Unicode 16-bit
		const wchar_t suits[4][3] = { L"\u2663" , L"\u2666", L"\u2665", L"\u2660" };//梅花，方塊，愛心，黑桃
		wcout << suits[suitToSelect]; //印出花色
		_setmode(_fileno(stdout), _O_TEXT);
	}

	void print()
	{
		vector<string> numbers = { "0","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
		if (suit != 4)
		{
			printSuit(suit);
			cout << numbers[number];
		}
		else
		{
			cout << "JOKER";
		}
	}
};
#endif