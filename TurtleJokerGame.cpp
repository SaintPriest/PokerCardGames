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
        vector <Deck> hands; //二維vector
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
            cout << names[i] << " 輪到你了!" << endl << endl;
            if (t < playerCount)
            {
                cout << "你的原始手牌: " << endl;
                hands[i].print();
                removePairs(hands[i]);
                cout << "已自動將對子的牌移除" << endl << endl;
            }
            cout << "前一玩家有" << hands[previous].deck.size() << "張牌" << endl;
            cout << "你的手牌: " << endl;
            hands[i].print();
            while (true)
            {
                cout << endl << "請選擇要抽的牌(1 ~ " << hands[previous].deck.size() << "):" << endl;
                cin >> input;
                cout << endl;
                if (input >= 1 && input <= hands[previous].deck.size())
                {
                    break;
                }
                else
                {
                    cout << "輸入錯誤..." << endl;
                }
            }
            Card card = hands[previous].draw(input - 1);
            hands[i].add(card);
            cout << "你抽到的牌: " << endl;
            card.print();
            cout << endl << endl << "你的手牌: " << endl;
            hands[i].print();
            int origSize = hands[i].deck.size();
            removePairs(hands[i]);
            if (hands[i].deck.size() != origSize)
            {
                cout << "已自動將對子的牌移除" << endl << endl;
                cout << "你的手牌: " << endl;
                hands[i].print();
            }
            if (hands[i].deck.size() == 0)
            {
                cout << endl << "你已獲勝" << endl;
            }
            if (hands[previous].deck.size() == 0)
            {
                cout << endl << names[previous] << " 已獲勝" << endl;
            }
            if (checkHands(i, hands) && hands[i].deck.size() == 2 && hands[i].deck[0].suit == 4 && hands[i].deck[1].suit == 4)
            {
                cout << names[i] << " 輸了..." << endl << endl;
                return;
            }
            cout << "請按[Enter]輪到下一位玩家..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
        }
    }
};
