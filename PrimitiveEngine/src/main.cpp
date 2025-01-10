#include "Game.h"
#include "Config.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
    game = new Game();

    const char* title = "PrimitiveEngine";

    game->Init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::WINDOWWIDTH, Config::WINDOWHEIGHT, false);

    while (game->Running())
    {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();

    return 0;
}
