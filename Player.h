#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>             // std::cout
#include <string>               // std::string
#include <vector>               // std::vector
#include <algorithm>            // std::sort

#include "Card.h"

class Player {
    public:
        Player();
        Player(int&, std::string&);
        ~Player();
        const int& getID() const;
        const std::string& getName() const;
        const int& getPoints() const;
        const std::vector<Card>& getHand() const;
        int getHandSize();
        Card& getPlayerCard(int&);
        const Card& getPlayerCard(int) const;
        void setID(int&);
        void setName(std::string&);
        void setPoints(int&);
        void setPlayerCard(Card&, int&);
        void orderHand(int&);
        void playCard(int&);
        const int printHand() const;

    private:
        int id;
        std::string name;
        int points = 0;
        std::vector<Card> hand;         
};

#endif

