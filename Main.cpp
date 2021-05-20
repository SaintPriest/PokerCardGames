#include <iostream>
#include "NineNineGame.cpp"

using namespace std;

int main()
{
    int playerCount = 4;
    vector<string> names = { "P1", "P2",  "P3", "P4" };
    NineNineGame game(playerCount, names);
    game.play();
}
