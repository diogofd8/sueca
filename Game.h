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
        GameSettings(int,int,std::array<Player,4>*);
        ~GameSettings();
        const int getID() const;
        const int getPlayedTurns() const;
        const int getTrumpSuit() const;
        const std::array<Player,4>& getPlayers() const;
        const Player& getPlayer(int) const;
        Player& getPlayer(int);
        const int getWinnerTeam() const;
        void setTrumpSuit(int);
        void setPlayers(std::array<Player,4>*);
        void setPlayerPoints(int,int);
        void printTrumpSuit() const;
        int calcWinnerTeam();

    private:
        int ID;
        int playedTurns;
        int trumpSuit;
        int winnerTeam;
        std::array<Player,4>* gamer;
};

class GameTurn : public GameSettings {
    public:
        GameTurn();
        GameTurn(int, int, int, int, std::array<Player,4>*);
        ~GameTurn();
        const int getNO() const;
        const int getStartingPlayer() const;
        const int getPlayedSuit() const;
        const int getTurnWinner() const;
        const int getPoints() const;
        void setPlayedSuit(int);
        void setPoints(int);
        void setPlayedCard(Card&);  
        void printTable();
        void calcTurnWinner();     
        void playTurn(); 

    private:
        int NO;
        int startingPlayer;
        int playedSuit;
        int turnWinner;
        int points;
        std::vector<Card> tableCard;
        std::vector<int> tableOrder;
};

#endif