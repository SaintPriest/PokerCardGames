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
        vector <Deck> hands; //�G��vector
        Deck deck;
        deck.shuffle();
        hands = deck.deal(playerCount, 5); //�C�쪱�a5�i�P
        for (int i = 0;;)
        {
            assignedNext = false;
            i = next; //next�b�W�@�^�X�Q���w
            cout << names[i] << " ����A�F!" << endl << endl;
            cout << "�ثe��Score: " << score << endl;
            while (true)
            {
                hands[i].print();
                cout << "�п�ܭn�X���P(1 ~ 5):" << endl;
                cin >> input;
                cout << endl;
                if (input >= 1 && input <= 5)
                {
                    break;
                }
                else
                {
                    cout << "��J���~..." << endl;
                }
            }
            Card card = hands[i].draw(input - 1);
            if (card.suit == 3 && card.number == 1) // �k�s
            {
                score = 0;
            }
            else if ((card.number >= 1 && card.number <= 3) || (card.number >= 6 && card.number <= 9)) //�֥[�Ʀr
            {
                score += card.number;
            }
            else if (card.number == 4) //�j��
            {
                clockwise = !clockwise;
            }
            else if (card.number == 5) //���w
            {
                while (true)
                {
                    cout << "�п�ܭn���w�����a(1 ~ " << playerCount << "):" << endl;
                    cin >> next;
                    if (next >= 1 && next <= playerCount)
                    {
                        next--;
                        assignedNext = true;
                        break;
                    }
                    else
                    {
                        cout << "��J���~..." << endl;
                    }
                }
                    
            }
            else if (card.number == 10)
            {
                int select = 0;
                while (true)
                {
                    cout << "�п�ܥ[10�δ�10:(0: �[10�A1: ��10)" << endl;
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
                        cout << "��J���~..." << endl;
                    }
                }
            }
            else if (card.number == 11) //PASS
            {
                cout << "PASS" << endl;
                cout << endl << "�Ы�[Enter]���~��..." << endl;
                cin.ignore();
                cin.get();
            }
            else if (card.number == 12)
            {
                int select = 0;
                while (true)
                {
                    cout << "�п�ܥ[20�δ�20:(0: �[20�A1: ��20)" << endl;
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
                        cout << "��J���~..." << endl;
                    }
                }
            }
            else if (card.number == 13) //����99
            {
                score = 99;
            }
            deck.add(card); //�⪱�a��X���P��^�P��
            hands[i].add(deck.draw(0)); //�q�P�襤��P
            if (score > 99)
            {
                system("cls");
                cout << "�ثe��Score: " << score << endl;
                cout << names[i] << "��F..." << endl << endl;
                break;
            }
            system("cls");
            if (assignedNext == false) //�S�����w�U�@�쪱�a
            {
                if (clockwise == true) //���ɰw�M�w�U�@�쪱�a
                {
                    next = (i + 1) % playerCount;
                }
                else
                {
                    next = (i + playerCount - 1) % playerCount; //�f�ɰw�M�w�U�@�쪱�a
                }
            }
            if (score < 0)
            {
                score = 0;
            }
        }
    }
};
