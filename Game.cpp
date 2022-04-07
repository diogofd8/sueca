#include "Game.h"

// GameSettings

GameSettings::GameSettings ()
{
    ID = 0;
    playedTurns = 0;
    trumpSuit = 0;
    winnerTeam = 0;
}

GameSettings::GameSettings (int _gameID, int _trumpSuit, std::array<Player,4> *_gamer)
{
    ID = _gameID;
    playedTurns = 0;
    trumpSuit = _trumpSuit;
    gamer = _gamer;
    winnerTeam = 0;
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

const std::array<Player,4>& GameSettings::getPlayers () const
{
    return *gamer;
}

const Player& GameSettings::getPlayer (int _index) const
{
    return (*gamer)[_index];
}

Player& GameSettings::getPlayer (int _index)
{
    return (*gamer)[_index];
}

const int GameSettings::getWinnerTeam() const
{
    return winnerTeam;
}

void GameSettings::setTrumpSuit (int _suit)
{
    trumpSuit = _suit;
    return;
}

void GameSettings::setPlayers (std::array<Player,4> *_gamer)
{
    gamer = _gamer;
    return;
}

void GameSettings::setPlayerPoints (int _index, int _points)
{
    (*gamer)[_index].setPoints(_points);
    return;
}

void GameSettings::printTrumpSuit () const
{
    std::string _suit;

    switch (trumpSuit) 
    {
        case 0: 
            _suit = "HEARTS";
            break;
        case 1:
            _suit = "DIAMONDS";
            break;
        case 2:
            _suit = "CLUBS";
            break;
        case 3:
            _suit = "SPADES";
            break;
    }

    std::cout << _suit;

    return;
}

int GameSettings::calcWinnerTeam ()
{   
    int pointsA = 0, pointsB = 0;

    for (auto i = 0; i < 4; ++i)
    {
        if (i%2 == 0)
            pointsA += getPlayer(i).getPoints();
        else pointsB += getPlayer(i).getPoints();
    }

    if (pointsA == pointsB)
    {
        winnerTeam = 0;
        return pointsA;
    }
    else if (pointsA > pointsB)
    {
        winnerTeam = 1;
        return pointsA;
    } 
    else winnerTeam = 2;
    return pointsB;

}

// GameTurn

GameTurn::GameTurn ()
{
    NO = 0;
    startingPlayer = 0;
    playedSuit = 0;
    turnWinner = 0;
    points = 0;
    points = 0;
}

GameTurn::GameTurn (int _NO, int _startingPlayer, int _ID, int _trumpSuit, std::array<Player,4> *_gamer)
: GameSettings(_ID, _trumpSuit, _gamer)
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
    tableCard.emplace_back(_card);
    return;
}

void GameTurn::printTable ()
{
    if (tableCard.size() == 0)
    {
        std::cout << "Table:" << std::endl;
        return;
    }

    std::cout << "Table: | ";

    for (auto i = 0; i < tableCard.size(); ++i)
    {
        std::cout << "(" << tableOrder[i] << ") " << getPlayer(tableOrder[i]).getName() << " - ";
        tableCard[i].printCard();
        std::cout << " | ";
    }

    std::cout << std::endl;
    return;
} 

void GameTurn::calcTurnWinner ()
{
    Card max, maxtrunfo;
    int winner, winnertrunfo;
    bool trunfo = false;

    if (tableCard.size() < 4)
    {   
        std::cout << "\t\t\tERROR: Round " << NO << " has" << tableCard.size() << " cards." << std::endl;
        return;
    }

    std::cout << std::endl;
    printTable();

    // Determining most valuable card
    for (auto i = 0; i < 4; ++i)
    {
        if ((tableCard[i].getSuit() == playedSuit) && (tableCard[i].getRank() > max.getRank()))
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

    if (trunfo)
        turnWinner = tableOrder[winnertrunfo];
    else turnWinner = tableOrder[winner];

    std::cout << "\t(" << turnWinner+1 << ") " << getPlayer(turnWinner).getName() << " wins!" << std::endl;
    setPlayerPoints(turnWinner, points);

    return;
}

void GameTurn::playTurn ()
{   
    for (auto p = startingPlayer; p < getPlayers().size(); ++p)
    {
        std::cout << "\t(" << p+1 << ") " << getPlayer(p).getName() << "'s turn!" << std::endl;

        if (getPlayer(p).printHand() == -1)
        {   
            std::cout << "\t\t\tERROR: Invalid hand!" << std::endl;
            return;
        }

        std::cout << std::endl;
        printTable();
        if (p != startingPlayer)
            std::cout << "\t -> Table Suit: " << tableCard[0].getRankStr();
        std::cout << "\t\t -> Table Trump: ";
        printTrumpSuit();    
        std::cout << "\n\nPick the number of the card you want to play: ";

        int playcard;
        std::cin >> playcard;

        while ((playcard > getPlayer(p).getHandSize()) || (playcard < 0))
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

        tableOrder.emplace_back(p);
        setPlayedCard(getPlayer(p).getPlayerCard(playcard));
        getPlayer(p).playCard(playcard);        
    }

    for (auto p = 0; p < startingPlayer; ++p)
    {
        std::cout << "\t(" << p+1 << ") " << getPlayer(p).getName() << "'s turn!" << std::endl;

        if (getPlayer(p).printHand() == -1)
        {   
            std::cout << "\t\t\tERROR: Invalid hand!" << std::endl;
            return;
        }

        std::cout << std::endl;
        printTable();
        std::cout << "\t -> Table Suit: " << tableCard[0].getRankStr();
        std::cout << "\t\t -> Table Trump: ";
        printTrumpSuit();    
        std::cout << "\n\nPick the number of the card you want to play: ";

        int playcard;
        std::cin >> playcard;

        while ((playcard > getPlayer(p).getHandSize()) || (playcard < 0))
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

        tableOrder.emplace_back(p);
        setPlayedCard(getPlayer(p).getPlayerCard(playcard));
        getPlayer(p).playCard(playcard);     
    }       

    return;
}