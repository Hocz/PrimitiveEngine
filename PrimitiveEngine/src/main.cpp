#include "Game.h"
#include "Config.h"

int main(int argc, char *argv[])
{
    const char* title = "PrimitiveEngine";

    Game::Instance().Init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::WINDOWWIDTH, Config::WINDOWHEIGHT, false);

    while (Game::Instance().Running())
    {
        Game::Instance().HandleEvents();
        Game::Instance().Update();
        Game::Instance().Render();
    }

    Game::Instance().Clean();

    return 0;
}
