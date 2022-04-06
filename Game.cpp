#include "Game.h"

GameSettings::GameSettings ()
{

}

GameSettings::GameSettings (int _gameID, int _trumpSuit, std::array<Player,4> *_gamer)
{
    ID = _gameID;
    playedTurns = 0;
    trumpSuit = _trumpSuit;
    gamer = _gamer;
}

GameSettings::GameSettings (int _gameID, int _trumpSuit)
{
    ID = _gameID;
    playedTurns = 0;
    trumpSuit = _trumpSuit;
}

GameSettings::~GameSettings ()
{

}

const int GameSettings::getID () const
{
    return ID;
}

const int GameSettings::getPlayedTurns () const
{
    return playedTurns; 
}

const int GameSettings::getTrumpSuit () const
{
    return trumpSuit;
}

const Player& GameSettings::getPlayer (int _index) const
{
    return (*gamer)[_index];
}

const std::array<Player,4>& GameSettings::getPlayers () const
{
    return *gamer;
}

void GameSettings::setTrumpSuit (int _suit)
{
    trumpSuit = _suit;
    return;
}

void GameSettings::setPlayer (Player &_player, int &_index)
{
    (*gamer)[_index] = _player;
    return;
}

void GameSettings::setPlayerPoints (int _index, int _points)
{
    (*gamer)[_index].setPoints(_points);
    return;
}

Player& GameSettings::PlayerSettings (int _index)
{
    return (*gamer)[_index];
}

/****************************************************************/

GameTurn::GameTurn ()
{
    NO = -1;
    startingPlayer = 0;
    points = 0;
}

GameTurn::GameTurn (int _NO, int _startingPlayer)
{
    NO = _NO;
    startingPlayer = _startingPlayer;
    points = 0;
}

GameTurn::~GameTurn ()
{
    
}

const int GameTurn::getNO () const
{
    return NO;
}

const int GameTurn::getStartingPlayer () const
{
    return startingPlayer;
}

const int GameTurn::getPlayedSuit () const
{
    return playedSuit;
}

const int GameTurn::getTurnWinner () const
{
    return turnWinner;
}

const int GameTurn::getPoints () const
{
    return points;
}

void GameTurn::setPlayedSuit (int _playedSuit)
{
    playedSuit = _playedSuit;
    return;
}

void GameTurn::setPoints (int _points)
{
    points += _points;
    return;
}

void GameTurn::setPlayedCard (Card &_card)
{
    tableCard.push_back(_card);
    return;
}

void GameTurn::calcTurnWinner ()
{
    Card max, maxtrunfo;
    int winner, winnertrunfo, points = 0;
    bool trunfo = false;

    if (tableCard.size() < 4)
    {   
        std::cout << "\t\t\tERROR: Round " << NO << " has" << tableCard.size() << " cards." << std::endl;
        return;
    }

    // Determining most valuable card
    for (auto i = 0; i < 4; ++i)
    {
        if (tableCard[i].getRank() > max.getRank())
        {
            max = tableCard[i];
            winner = i;
        }
            
        if ((tableCard[i].getSuit() == getTrumpSuit()) && (tableCard[i].getRank() > maxtrunfo.getRank()))
        {
            maxtrunfo = tableCard[i];
            trunfo = true;
            winnertrunfo = i;
        }

        // Adding points in the table
        setPoints(tableCard[i].getPoints());
    }
    
    // Adding table points to the winner player
    if (trunfo)
    {
        std::cout << "\t(" << winnertrunfo << ") " << getPlayer(winnertrunfo).getName() << " wins!" << std::endl;
        setPlayerPoints(winnertrunfo, points);
        turnWinner = winnertrunfo;
    }
    else
    {
        std::cout << "\t(" << winner << ") " << getPlayer(winner).getName() << " wins!" << std::endl;
        setPlayerPoints(winner, points);
        turnWinner = winner;
    }

    return;
}

void GameTurn::printTable ()
{
    std::cout << "Table: | ";

    for (auto i = 0; i < tableCard.size(); ++i)
    {
        std::cout << "(" << i << ") " << getPlayer(i).getName() << " - ";
        tableCard[i].printCard();
        std::cout << " | ";
    }

    std::cout << std::endl;
    return;
} 

void GameTurn::playTurn ()
{   
    for (auto p = startingPlayer; p < getPlayers().size(); ++p)
    {
        std::cout << "(" << p << ") " << getPlayer(p).getName() << "'s turn!" << std::endl;

        if (getPlayer(p).printHand() == -1)
        {   
            std::cout << "\t\t\tERROR: Invalid hand!" << std::endl;
            return;
        }

        std::cout << std::endl;
        printTable();
        if (p != startingPlayer)
            std::cout << "\t -> Table Suit: " << tableCard[0].getRankStr() << std::endl;
            
        std::cout << "\nPick the number of the card you want to play: ";

        int playcard;
        std::cin >> playcard;

        while ((playcard > 9) || (playcard < 0))
        {
            std::cout << "Invalid selection!\nPick the number of the card you want to play: ";
            std::cin >> playcard;
        }

        bool assist = false;
        if (p == startingPlayer)
            playedSuit = getPlayer(p).getPlayerCard(playcard).getSuit();

        for (auto i = 0; i < getPlayer(p).getHand().size(); ++i)
            if (getPlayer(p).getPlayerCard(i).getSuit() == playedSuit)
                assist = true;   

        while ((assist == true) && (getPlayer(p).getPlayerCard(playcard).getSuit() != playedSuit))
        {
            std::cout << "Invalid selection! Please respect the played suit: ";
            tableCard[0].printCard();
            std::cout << "\nPick the number of the card you want to play: ";
            std::cin >> playcard;
        }

        setPlayedCard(PlayerSettings(p).getPlayerCard(playcard));
        PlayerSettings(p).playCard(playcard);        
    }

    for (auto p = 0; p < startingPlayer; ++p)
    {
        std::cout << "\t(" << p << ") " << getPlayer(p).getName() << "'s turn!" << std::endl;

        if (getPlayer(p).printHand() == -1)
        {   
            std::cout << "\t\t\tERROR: Invalid hand!" << std::endl;
            return;
        }

        std::cout << std::endl;
        printTable();
        std::cout << "\t -> Table Suit: " << tableCard[0].getRankStr() << std::endl;    
        std::cout << "Pick the number of the card you want to play: ";

        int playcard;
        std::cin >> playcard;

        while ((playcard > 9) || (playcard < 0))
        {
            std::cout << "Invalid selection!\nPick the number of the card you want to play: ";
            std::cin >> playcard;
        }

        bool assist = false;

        for (auto i = 0; i < getPlayer(p).getHand().size(); ++i)
        {
            if (getPlayer(p).getPlayerCard(i).getSuit() == playedSuit)
                assist = true;   
        }

        while ((assist == true) && getPlayer(p).getPlayerCard(playcard).getSuit() != playedSuit)
        {
            std::cout << "Invalid selection! Please respect the played suit: ";
            tableCard[0].printCard();
            std::cout << "\nPick the number of the card you want to play: ";
            std::cin >> playcard;
        }

        setPlayedCard(PlayerSettings(p).getPlayerCard(playcard));
        PlayerSettings(p).playCard(playcard);     
    }       

    return;
}