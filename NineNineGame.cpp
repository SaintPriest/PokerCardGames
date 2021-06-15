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
        hands = deck.deal(playerCount, 5); //每位玩家5張牌
        for (int i = 0;;)
        {
            assignedNext = false;
            i = next; //next在上一回合被指定
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
            else if ((card.number >= 1 && card.number <= 3) || (card.number >= 6 && card.number <= 9)) //累加數字
            {
                score += card.number;
            }
            else if (card.number == 4) //迴轉
            {
                clockwise = !clockwise;
            }
            else if (card.number == 5) //指定
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
            else if (card.number == 11) //PASS
            {
                cout << "PASS" << endl;
                cout << endl << "請按[Enter]鍵繼續..." << endl;
                cin.ignore();
                cin.get();
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
            else if (card.number == 13) //直接99
            {
                score = 99;
            }
            deck.add(card); //把玩家丟出的牌放回牌堆
            hands[i].add(deck.draw(0)); //從牌堆中抽牌
            if (score > 99)
            {
                system("cls");
                cout << "目前的Score: " << score << endl;
                cout << names[i] << "輸了..." << endl << endl;
                break;
            }
            system("cls");
            if (assignedNext == false) //沒有指定下一位玩家
            {
                if (clockwise == true) //順時針決定下一位玩家
                {
                    next = (i + 1) % playerCount;
                }
                else
                {
                    next = (i + playerCount - 1) % playerCount; //逆時針決定下一位玩家
                }
            }
            if (score < 0)
            {
                score = 0;
            }
        }
    }
};
