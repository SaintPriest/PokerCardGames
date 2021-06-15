#ifndef DECK_CPP
#define DECK_CPP
#include <iostream>
#include <vector>
#include <algorithm>
#include "Card.cpp"

using namespace std;

class Deck
{
public:
	Deck(bool empty = false, bool enableJoker = false)
	{
		if (empty == false) //�D�ŵP��
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 1; j < 14; j++)
				{
					deck.push_back(Card(i, j));
				}
			}
			if (enableJoker == true)
			{
				deck.push_back(Card(4, 14));
				deck.push_back(Card(4, 15));
			}
		}
	}
	vector <Card> deck;
	void shuffle()
	{
		random_shuffle(deck.begin(), deck.end()); // �~�P
	}

	vector <Deck> deal(int playerCount, int handCardCount) //�C�쪱�a�ohandCardCount�i�P
	{
		vector <Deck> hands;
		for (size_t i = 0; i < playerCount; i++)
		{
			Deck handDeck(true);
			handDeck.deck.clear();
			for (size_t j = 0; j < handCardCount; j++)
			{
				handDeck.deck.push_back(deck[i * handCardCount + j]);
			}
			hands.push_back(handDeck);
		}
		deck.erase(deck.begin(), deck.begin() + (size_t)playerCount * handCardCount);
		return hands;
	}

	vector <Deck> dealAll(int playerCount) //�P�����o��
	{
		vector <Deck> hands;
		vector <int> handCardCount; //�C�ӤH�����P�ƶq
		int deckIndex = 0;
		for (int i = 0; i < playerCount; i++)
		{
			if (i < deck.size() % playerCount) //�e�����H�����P�ƶq�h1�i
			{
				handCardCount.push_back(deck.size() / playerCount + 1);
			}
			else
			{
				handCardCount.push_back(deck.size() / playerCount);
			}
		}
		for (int i = 0; i < playerCount; i++)
		{
			Deck handDeck(true);
			handDeck.deck.clear();
			for (int j = 0; j < handCardCount[i]; j++)
			{
				handDeck.deck.push_back(deck[deckIndex++]);
			}
			hands.push_back(handDeck);
		}
		deck.erase(deck.begin(), deck.end());
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

	Card draw(int index) //��P�q�P�襤���X
	{
		Card card = deck[index];
		deck.erase(deck.begin() + index);
		return card;
	}

	void add(Card card) //��P�[�J�P��
	{
		deck.push_back(card);
	}
};
#endif