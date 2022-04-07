#include <iostream>             // std::cout
#include <algorithm>            // std::shuffle
#include <array>                // std::array
#include <string>               // std::string
#include <random>               // std::default_random_engine
#include <chrono>               // std::chrono::system_clock

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

int main ()
{
    int gameID = 0, shuffle = 1;
    bool sueca = true;
    std::string input;

    Deck gamedeck;
    std::array<Player,4> _player;

    std::cout << "\t\t\t.:: Jogo da Sueca ::." << std::endl;
    std::cout << "\n=====================================================================\n" << std::endl;

    while (sueca)
    {   
        // Arrange Deck
        std::cout << "How many times do you want to shuffle the deck? ";
        std::cin >> shuffle;

        while (shuffle < 1)
        {
            std::cout << "Please insert an integer bigger than 0.\nHow many times do you want to shuffle the deck? ";
            std::cin >> shuffle;
        }

        gamedeck.shuffleDeck(shuffle);

        std::cout << "Deck shuffled " << shuffle << " times!" << std::endl;
        std::cout << "\n\t * The player pairings will be (1 & 3) and (2 & 4).\n" << std::endl;

        // Set the Players
        if (gameID == 0)
        {   
            std::cout << "Let's proceed to name each player.\n" << std::endl;
            std::string playername;
            for (auto i = 0; i < 4; ++i)
            {
                std::cout << "Type the name of Player " << i+1 << ": ";
                std::cin >> playername;

                while (playername.size() == 0)
                {
                    std::cout << "Please insert a readable name.\nType the name of Player " << i+1 << ": ";
                    std::cin >> playername;
                }

                _player[i].setID(i);
                _player[i].setName(playername);
            }
        }

        for (auto i = 0; i < 4; ++i)
            for (auto c = 0; c < 10; c++)
                _player[i].setPlayerCard(gamedeck.getDeckCard(c+i*10), c);

        
        // Set the trump card
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> randomplayer(0,3);
        int trumpOwner = randomplayer(generator);

        std::cout << "\nThe trump card is (" << trumpOwner+1 << ") " << _player[trumpOwner].getName() << "'s ";
        _player[trumpOwner].getPlayerCard(0).printCard();
        std::cout << std::endl;
        int trumpSuit = _player[trumpOwner].getPlayerCard(0).getSuit();

        // Create Game instance
        GameSettings suecaGame(gameID, trumpSuit, &_player);

        // Play Turns
        std::array<GameTurn*,10> suecaTurnHistory;
        int startingPlayer = trumpOwner;
        
        for (auto i = 0; i < 10; ++i)
        {
            GameTurn suecaTurn(i, startingPlayer, gameID, trumpSuit, &_player);
            std::cout << "\n\t\t\t.:: Round " << i+1 << " ::." << std::endl;

            suecaTurn.playTurn();
                        
            std::cout << "---------------------------------------------------------------------" << std::endl;
            
            suecaTurn.calcTurnWinner();
            startingPlayer = suecaTurn.getTurnWinner();
            
            std::cout << "=====================================================================\n" << std::endl;
            suecaTurnHistory[i] = &suecaTurn;
        }
        
        int winnerTeamPts = suecaGame.calcWinnerTeam();

        if (suecaGame.getWinnerTeam() == 0)
            std::cout << "This game ended in a tie!" << std::endl;
        else if (suecaGame.getWinnerTeam() == 1)
            std::cout << "Team (1 & 3) wins with " << winnerTeamPts << " points!" << std::endl;
        else if (suecaGame.getWinnerTeam() == 2)
            std::cout << "Team (2 & 4) wins with " << winnerTeamPts << " points!" << std::endl;
        else std::cout << "Error: Couldn't find a winner." << std::endl;
        
        std::cout << "The game has finished! The winners are: " << "\n\nPlay another round? [Y/n] ";
        std::cin >> input;
        if ((input == "Y") || (input == "y") || (input == "yes") || (input == "YES") || (input == "Yes"))
        {
            gameID++;
            std::cout << "\n=====================================================================\n" << std::endl;
            std::cout << "Game number " << gameID+1 << "!\n" << std::endl; 
        }
            
        else if ((input == "N") || (input == "n") || (input == "no") || (input == "NO") || (input == "No"))
        {
            std::cout << "\nUntil next time!" << std::endl;
            sueca = false;
        }
            
        else 
        {
            std::cout << "\nInvalid input! I'll take it as a no, until next time!" << std::endl;
            sueca = false;
        }
    }

    return 0;
}

// int main ()
// {
//     std::cout << "\t\t\t.:: Jogo da Sueca ::." << std::endl;
//     std::cout << "\n=====================================================================\n" << std::endl;

//     Game sueca;
//     int order = 0;
//     sueca.startGame();

//     std::cout << "\n=====================================================================\n" << std::endl;

//     for (auto n = 0; n < sueca.getRound().size(); ++n)
//     {   
//         sueca.startRound(n);
//         std::cout << "\t\t\t.:: Round " << n+1 << " ::." << std::endl;
//         sueca.getRound()[n].playTurn(order);
//         std::cout << "---------------------------------------------------------------------" << std::endl;
//         order = sueca.getRound()[n].getTurnWinner();
//         std::cout << order << std::endl;
//         std::cout << "=====================================================================\n" << std::endl;
//     } 
    
//     return 0;
// }

// int main ()
// {
//     std::array<std::string,4> players = {"p1", "p2", "p3", "p4"};
//     int order, aux = -1, max = 0;
//     bool flag = false;

//     std::cin >> order;

//     while (order >= players.size() || order < 0)
//     {
//         std::cout << "invalid number" << std::endl;
//         std::cin >> order;
//     }

//     while (order != aux)
//     {
//         if (flag == false)
//         {
//             aux = order;
//             flag = true;
//         }
    
//         std::cout << "(" << aux << ") " << players[aux] << std::endl;
//         aux++;

//         if (aux == players.size())
//             aux = 0;
//     }

//     /*for (auto i = order; i < players.size(); ++i)
//         std::cout << "(" << i << ") " << players[i] << std::endl;

//     for (auto i = 0; i < order; ++i)
//         std::cout << "(" << i << ") " << players[i] << std::endl;*/

//     return 0;
// }



/* cards
    suits
        0 - hearts
        1 - diamonds
        2 - clubs
        3 - spades
    rank
        0 - two
        1 - three
        2 - four
        3 - five
        4 - six
        5 - queen
        6 - jack
        7 - king
        8 - seven
        9 - ace
*/