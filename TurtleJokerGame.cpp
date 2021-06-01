#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "Deck.cpp"

using namespace std;
class TurtleJokerGame
{
public:
    int playerCount;
    vector <string> names;
    TurtleJokerGame(int playerCount, vector <string> names)
    {
        this->playerCount = playerCount;
        this->names = names;
    }
    bool checkHands(int index, vector <Deck> hands)
    {
        for (int i = 0; i < playerCount; i++)
        {
            if (i != index && hands[i].deck.size() > 0)
            {
                return false;
            }
        }
        return true;
    }
    void removePairs(Deck &deck)
    {
        for (int i = 0; i < deck.deck.size(); i++)
        {
            for (int j = i + 1; j < deck.deck.size(); j++)
            {
                if (deck.deck[i].number == deck.deck[j].number)
                {
                    deck.deck.erase(deck.deck.begin() + j);
                    deck.deck.erase(deck.deck.begin() + i);
                    i = -1;
                    break;
                }
            }
        }
    }
    void play()
    {
        int input = 0;
        int i = playerCount - 1;
        int previous;
        vector <Deck> hands; //�G��vector
        Deck deck(false, true);
        deck.shuffle();
        hands = deck.dealAll(playerCount);
        for (int t = 0;;t++)
        {
            while (true)
            {
                i = (i + 1) % playerCount;
                if (hands[i].deck.size() != 0)
                {
                    break;
                }
            }
            previous = i;
            while (true)
            {
                previous = (previous + playerCount - 1) % playerCount;
                if (hands[previous].deck.size() != 0)
                {
                    break;
                }
            }
            system("cls");
            cout << names[i] << " ����A�F!" << endl << endl;
            if (t < playerCount)
            {
                cout << "�A����l��P: " << endl;
                hands[i].print();
                removePairs(hands[i]);
                cout << "�w�۰ʱN��l���P����" << endl << endl;
            }
            cout << "�e�@���a��" << hands[previous].deck.size() << "�i�P" << endl;
            cout << "�A����P: " << endl;
            hands[i].print();
            while (true)
            {
                cout << endl << "�п�ܭn�⪺�P(1 ~ " << hands[previous].deck.size() << "):" << endl;
                cin >> input;
                cout << endl;
                if (input >= 1 && input <= hands[previous].deck.size())
                {
                    break;
                }
                else
                {
                    cout << "��J���~..." << endl;
                }
            }
            Card card = hands[previous].draw(input - 1);
            hands[i].add(card);
            cout << "�A��쪺�P: " << endl;
            card.print();
            cout << endl << endl << "�A����P: " << endl;
            hands[i].print();
            int origSize = hands[i].deck.size();
            removePairs(hands[i]);
            if (hands[i].deck.size() != origSize)
            {
                cout << "�w�۰ʱN��l���P����" << endl << endl;
                cout << "�A����P: " << endl;
                hands[i].print();
            }
            if (hands[i].deck.size() == 0)
            {
                cout << endl << "�A�w���" << endl;
            }
            if (hands[previous].deck.size() == 0)
            {
                cout << endl << names[previous] << " �w���" << endl;
            }
            if (checkHands(i, hands) && hands[i].deck.size() == 2 && hands[i].deck[0].suit == 4 && hands[i].deck[1].suit == 4)
            {
                cout << names[i] << " ��F..." << endl << endl;
                return;
            }
            cout << "�Ы�[Enter]����U�@�쪱�a..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
        }
    }
};
