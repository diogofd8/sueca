#ifndef GAME_H
#define GAME_H

#include <iostream>             // std::cout
#include <algorithm>            // std::shuffle
#include <array>                // std::array
#include <string>               // std::string
#include <random>               // std::default_random_engine
#include <chrono>               // std::chrono::system_clock

#include "Deck.h"
#include "Player.h"

class GameSettings : public Deck {
    public:
        GameSettings();
        GameSettings(int, int, std::array<Player,4>*);
        GameSettings(int, int);
        ~GameSettings();
        const int getID() const;
        const int getPlayedTurns() const;
        const int getTrumpSuit() const;
        const Player& getPlayer(int) const;
        const std::array<Player,4>& getPlayers() const;
        void setTrumpSuit(int);
        void setPlayer(Player&, int&);
        void setPlayerPoints(int,int);
        Player& PlayerSettings(int);

    private:
        int ID;
        int playedTurns;
        int trumpSuit;
        std::array<Player,4>* gamer;
};

class GameTurn : public GameSettings {
    public:
        GameTurn();
        GameTurn(int,int);
        ~GameTurn();
        const int getNO() const;
        const int getStartingPlayer() const;
        const int getPlayedSuit() const;
        const int getTurnWinner() const;
        const int getPoints() const;
        void setPlayedSuit(int);
        void setPoints(int);
        void setPlayedCard(Card&);  
        void calcTurnWinner(); 
        void printTable();    
        void playTurn(); 

    private:
        int NO;
        int startingPlayer;
        int playedSuit;
        int turnWinner;
        int points;
        std::vector<Card> tableCard;
};

#endif