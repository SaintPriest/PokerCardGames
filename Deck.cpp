#include <iostream>
#include <vector>
#include <algorithm>
#include "Card.cpp"

using namespace std;

class Deck
{
public:
	Deck(bool empty = false)
	{
		if (empty == false)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 1; j < 14; j++)
				{
					deck.push_back(Card(i, j));
				}
			}
		}
	}
	vector <Card> deck;
	void shuffle()
	{
		random_shuffle(deck.begin(), deck.end()); // ¬~µP
	}

	vector <Deck> deal(int playerCount, int handCardCount)
	{
		vector <Deck> hands;
		for (int i = 0; i < playerCount; i++)
		{
			Deck handDeck(true);
			handDeck.deck.clear();
			for (int j = 0; j < handCardCount; j++)
			{
				handDeck.deck.push_back(deck[i * handCardCount + j]);
			}
			hands.push_back(handDeck);
		}
		return hands;
	}

	void print()
	{
		for (int i = 0; i < deck.size(); i++)
		{
			deck[i].print();
			cout << " ";
		}
		cout << endl;
	}

	Card draw(int index)
	{
		Card card = deck[index];
		deck.erase(deck.begin() + index);
		return card;
	}
	void add(Card card)
	{
		deck.push_back(card);
	}
};