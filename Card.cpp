#include "Card.h"

Card::Card ()
{
    suit = -1;
    rank = -1;
}

Card::Card (int &_suit, int &_rank)
{
    suit = _suit;
    rank = _rank;
}

Card::~Card ()
{

}

const int& Card::getSuit () const
{
    return suit;
}

const std::string Card::getRankStr () const
{   
    std::string _suit;
    switch (suit) 
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

    return _suit;
}

const int& Card::getRank () const
{
    return rank;
}

void Card::setSuit (int &_suit) 
{
    suit = _suit;
    return;
}

void Card::setRank (int &_rank) 
{
    rank = _rank;
    return;
}

void Card::setCard (int &_suit, int &_rank)
{
    suit = _suit;
    rank = _rank;
}

const int Card::getPoints () const
{
    if (rank <= 4)
        return 0;
    else if (rank <= 7)
        return rank-3;
    else
        return rank+2;
}

void Card::printCard () const
{
    std::string naipe, nome;
    switch (suit) 
    {
        case 0: 
            naipe = "HEARTS";
            break;
        case 1:
            naipe = "DIAMONDS";
            break;
        case 2:
            naipe = "CLUBS";
            break;
        case 3:
            naipe = "SPADES";
            break;
    }
    switch (rank)
    {
        case 0: 
            nome = "TWO";
            break;
        case 1:
            nome = "THREE";
            break;
        case 2:
            nome = "FOUR";
            break;
        case 3:
            nome = "FIVE";
            break;
        case 4:
            nome = "SIX";
            break;
        case 5:
            nome = "QUEEN";
            break;
        case 6:
            nome = "JACK";
            break;
        case 7:
            nome = "KING";
            break;
        case 8:
            nome = "SEVEN";
            break;
        case 9:
            nome = "ACE";
            break;
    }

    std::cout << nome << " of " << naipe;
    return;
}