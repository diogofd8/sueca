#ifndef CARD_H
#define CARD_H

#include <iostream>             // std::cout
#include <string>               // std::string

class Card {
    public:
        Card();
        Card(int&, int&);
        ~Card();
        const int& getSuit() const;
        const int& getRank() const;
        const std::string getRankStr() const;
        const int getPoints() const;
        void printCard () const;
        void setSuit(int&); 
        void setRank(int&);
        void setCard(int&, int&);

    private:
        int suit;
        int rank;
};

#endif