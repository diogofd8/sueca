#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>             // std::cout
#include <string>               // std::string
#include <vector>               // std::vector

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
        Card& getPlayerCard(int&);
        const Card& getPlayerCard(int) const;
        void setID(int&);
        void setName(std::string&);
        void setPoints(int&);
        void setPlayerCard(Card&, int&);
        void playCard(int&);
        const int printHand() const;

    private:
        int id;
        std::string name;
        int points = 0;
        std::vector<Card> hand;         
};

#endif


/*

// READS THE WHOLE VECTOR
const std::vector<int>& GetVect() const
{
    return vect;
}


class X {
    std::array<double, 9> array;
public:
    std::array<double, 9> const & GetArray() const {return array;}
};

X x;
double d = x.GetArray()[5]; // read-only access, no copy

auto array = x.GetArray();  // get a copy
array[5] = 42;              // modify the copy
*/