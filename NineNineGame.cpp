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
        vector <Deck> hands; //二維vector
        Deck deck;
        deck.shuffle();
        hands = deck.deal(playerCount, 5);
        while (score <= 99)
        {

            for (int i = 0; i < playerCount;)
            {
                i = next;
                cout << "目前的Score: " << score << endl;
                hands[i].print();
                cout << "請選擇要出的牌(1 ~ 5):" << endl;
                cin >> input;
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
                    cout << "請選擇要指定的玩家(1 ~ " << playerCount << "):" << endl;
                    cin >> next;
                    next--;
                }
                deck.add(card);
                hands[i].add(deck.draw(0));
                if (score > 99)
                {
                    cout << i + 1 << "玩家輸了" << endl;
                    break;
                }
                if (clockwise == true)
                {
                    next = (i + 1) % playerCount;
                }
                else
                {
                    next = (i + playerCount - 1) % playerCount;
                }
            }
        }
    }
};
