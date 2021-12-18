#include "Game.h"

int main()
{
    srand((unsigned)time(0));

    Game game;

    game.Init();
    game.Run();

    return 0;
}