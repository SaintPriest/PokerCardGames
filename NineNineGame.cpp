#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "Deck.cpp"

using namespace std;
class NineNineGame
{
public:
    int playerCount;
    vector <string> names;
    NineNineGame(int playerCount, vector <string> names)
    {
        this->playerCount = playerCount;
        this->names = names;
    }
    void play()
    {
        int cardCount = 52;
        int score = 0;
        int input = 0;
        int next = 0;
        bool clockwise = true;
        bool assignedNext = false;
        vector <Deck> hands; //二維vector
        Deck deck;
        deck.shuffle();
        hands = deck.deal(playerCount, 5);
        for (int i = 0;;)
        {
            assignedNext = false;
            i = next;
            cout << names[i] << " 輪到你了!" << endl << endl;
            cout << "目前的Score: " << score << endl;
            while (true)
            {
                hands[i].print();
                cout << "請選擇要出的牌(1 ~ 5):" << endl;
                cin >> input;
                cout << endl;
                if (input >= 1 && input <= 5)
                {
                    break;
                }
                else
                {
                    cout << "輸入錯誤..." << endl;
                }
            }
            Card card = hands[i].draw(input - 1);
            if (card.suit == 3 && card.number == 1) // 歸零
            {
                score = 0;
            }
            else if ((card.number >= 1 && card.number <= 3) || (card.number >= 6 && card.number <= 9))
            {
                score += card.number;
            }
            else if (card.number == 4)
            {
                clockwise = !clockwise;
            }
            else if (card.number == 5)
            {
                while (true)
                {
                    cout << "請選擇要指定的玩家(1 ~ " << playerCount << "):" << endl;
                    cin >> next;
                    if (next >= 1 && next <= playerCount)
                    {
                        next--;
                        assignedNext = true;
                        break;
                    }
                    else
                    {
                        cout << "輸入錯誤..." << endl;
                    }
                }
                    
            }
            else if (card.number == 10)
            {
                int select = 0;
                while (true)
                {
                    cout << "請選擇加10或減10:(0: 加10，1: 減10)" << endl;
                    cin >> select;
                    if (select == 0)
                    {
                        score += 10;
                        break;
                    }
                    else if (select == 1)
                    {
                        score -= 10;
                        break;
                    }
                    else
                    {
                        cout << "輸入錯誤..." << endl;
                    }
                }
            }
            else if (card.number == 11)
            {
                cout << "PASS" << endl;
            }
            else if (card.number == 12)
            {
                int select = 0;
                while (true)
                {
                    cout << "請選擇加20或減20:(0: 加20，1: 減20)" << endl;
                    cin >> select;
                    if (select == 0)
                    {
                        score += 20;
                        break;
                    }
                    else if (select == 1)
                    {
                        score -= 20;
                        break;
                    }
                    else
                    {
                        cout << "輸入錯誤..." << endl;
                    }
                }
            }
            else if (card.number == 13)
            {
                score = 99;
            }
            else
            {
                cout << "System ERROR: Unknown card number!" << endl;
                throw exception();
            }
            deck.add(card);
            hands[i].add(deck.draw(0));
            if (score > 99)
            {
                system("cls");
                cout << "目前的Score: " << score << endl;
                cout << names[i] << "輸了..." << endl << endl;
                break;
            }
            if (assignedNext == false)
            {
                if (clockwise == true)
                {
                    next = (i + 1) % playerCount;
                }
                else
                {
                    next = (i + playerCount - 1) % playerCount;
                }
            }
            if (score < 0)
            {
                score = 0;
            }
        }
        
    }
};
