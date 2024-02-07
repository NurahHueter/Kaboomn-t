/*
MultimediaTechnology / FH Salzburg
MultimediaProjekt 2A
Authors: Nurah Hüter, Florian Rauter
*/
#include "pch.h"
#include "Game.h"

    int main()
    {
        {
            std::unique_ptr<mmt_gd::Game> game = std::make_unique<mmt_gd::Game>();
            game->Run();
        }
        return 0;
    }
