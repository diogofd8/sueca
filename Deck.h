#ifndef DECK_H
#define DECK_H

#include <iostream>             // std::cout
#include <algorithm>            // std::shuffle
#include <array>                // std::array
#include <string>               // std::string
#include <random>               // std::default_random_engine
#include <chrono>               // std::chrono::system_clock

#include "Card.h"

class Deck {
    public:
        Deck();
        ~Deck();
        void shuffleDeck(int&); 
        void printDeck();
        Card& getDeckCard(int&);
        Card& getDeckCard(int);   

    private:
        std::array<Card,40> element;         
};

#endif
