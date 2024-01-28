#pragma once
#include "pch.h"
#include "Game.h"

    int main()
    {
        {
            std::cout << "Läuft ;)" << std::endl;
            std::unique_ptr<mmt_gd::Game> game = std::make_unique<mmt_gd::Game>();
            game->Run();
            std::cout << "Endlich Fertig <.<" << std::endl;
        }
        return 0;
    }
