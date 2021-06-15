#include <iostream>
#include <ctime>
#include <fstream>
#include "NineNineGame.cpp"
#include "TurtleJokerGame.cpp"

using namespace std;

int GameSetting()
{
    int select = 0;
    system("cls");
    while (true)
    {
        cout << "//////////PRGM Settings//////////" << endl;
        cout << "0. 返回" << endl;
        cout << "1. 更改玩家名稱" << endl;
        cout << "2. 重新載入玩家名稱" << endl;
        cin >> select;
        switch (select)
        {
            case 0:
            {
                system("cls");
                return 0;
            }
            case 1:
            {
                system("cls");
                cout << "更改玩家名稱請至names.txt中修改，每一行為每位玩家的名稱" << endl;
                cout << "修改完後請執行2. 程式設定-> 2. 重新載入玩家名稱選項" << endl;
                return 0;
            }
            case 2:
            {
                return 1;
            }
            default:
            {
                cout << "輸入錯誤..." << endl;
                continue;
            }
        }
    }
}

void SelectGame(int playerCount, vector<string> names)
{
    int select = 0;
    system("cls");
    while (true)
    {
        cout << "//////////Game Select//////////" << endl;
        cout << "0. 返回" << endl;
        cout << "1. 九九" << endl;
        cout << "2. 抽鬼牌" << endl;
        cin >> select;
        switch (select)
        {
            case 0:
            {
                system("cls");
                return;
            }
            case 1:
            {
                system("cls");
                NineNineGame game(playerCount, names);
                game.play();
                return;
            }
            case 2:
            {
                system("cls");
                TurtleJokerGame game(playerCount, names);
                game.play();
                return;
            }
            default:
            {
                system("cls");
                cout << "輸入錯誤..." << endl;
                continue;
            }
        }
    }
}

int main()
{
    int playerCount = 4, select = 0;
    fstream file; 
    file.open("names.txt", fstream::in | fstream::out | fstream::app); //若檔案不存在則自動創檔
    srand(time(0));
    vector<string> names;
    if (file.peek() != fstream::traits_type::eof()) //檔案是否為空
    {
        cout << "Names File existed" << endl;
        int checkPlayerCount = 0;
        while (!file.eof())
        {
            string name;
            file >> name;
            names.push_back(name);
            checkPlayerCount++;
        }
        cout << "將會有" << checkPlayerCount - 1 << "位玩家遊玩" << endl;
        cout << "玩家人數依照txt檔內名字數量決定" << endl;
        playerCount = checkPlayerCount - 1;
        file.close();
    }
    else
    {
        int checkPlayerCount = 0;
        while (true)
        {
            cout << "有幾位玩家遊玩?(2 ~ 6)" << endl;
            cin >> checkPlayerCount;
            if (checkPlayerCount >= 2 && checkPlayerCount <= 6)
            {
                break;
            }
            else
            {
                cout << "輸入無效..." << endl;
            }
        }
        playerCount = checkPlayerCount;
        system("cls");
        file.clear(); //檔案指標重製
        cout << "Creating Names data" << endl;
        for (int i = 0; i < playerCount; i++)
        {
            names.push_back("Player" + to_string(i + 1));
            string name = "Player" + to_string(i + 1);
            file << name << endl;
        }
        cout << "Names Data Created!" << endl;
        file.close();
    }
    while (true)
    {
        cout << "//////////MAIN MENU//////////" << endl;
        cout << "1. 選擇遊戲" << endl;
        cout << "2. 程式設定" << endl;
        cout << "3. 離開" << endl;
        cin >> select;
        switch (select)
        {
            case 1:
            {
                SelectGame(playerCount, names);
                break;
            }
            case 2:
            {
                if (GameSetting())
                {
                    file.open("names.txt", fstream::in | fstream::out | fstream::app);
                    int end = names.size();
                    for (int i = 0; i < end; i++)
                    {
                        names.erase(names.begin());
                    }
                    while (!file.eof())
                    {
                        string name;
                        file >> name;
                        names.push_back(name);
                    }
                    file.close();
                    system("cls");
                    cout << "操作已完成" << endl;
                }
                break;
            }
            case 3:
            {
                exit(0);
            }
            default:
            {
                system("cls");
                cout << "輸入錯誤..." << endl;
                continue;
            }
        }
    }
}
