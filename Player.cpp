#include "Player.h"

Player::Player ()
{
    id = -1;
    points = 0;
}

Player::Player (int &_id, std::string &_name)
{
    id = _id;
    name = _name;
    points = 0;
}

Player::~Player ()
{
    
}

const int& Player::getID () const
{
    return id;
}

const std::string& Player::getName () const
{
    return name;
}

const int& Player::getPoints () const
{
    return points;
}

const std::vector<Card>& Player::getHand() const
{
    return hand;
}

Card& Player::getPlayerCard (int &index)
{
    return hand[index];
}

const Card& Player::getPlayerCard (int index) const
{
    return hand[index];
}

void Player::setID (int &_id)
{
    id = _id;
    return;
}

void Player::setName (std::string &_name)
{
    name = _name;
    return;
}

void Player::setPoints (int &_points)
{
    points += _points;
    return;
}

void Player::setPlayerCard (Card &_card, int &_index)
{
    if (_index > 10)
    {
        std::cout << "\t\t\tERROR: Player " << name << " already has 10 cards (" << id << ")" << std::endl;
        return;
    }

    hand.emplace_back(_card);
    return;
}

void Player::playCard (int &_index)
{
    hand.erase(hand.begin()+_index);
    return;
}

const int Player::printHand () const
{
    if (hand.size() == 0)
    {
        std::cout << "\t\t\tERROR: Player " << name << " has no cards (" << id << ")" << std::endl;
        return -1;
    }

    std::cout << "\t(" << id << ") " << name << "'s cards:" << std::endl;
    for (auto i = 0; i < hand.size(); ++i)
    {   
        std::cout << "\t\t(" << i << ") ";
        hand[i].printCard();
        std::cout << std::endl;
    }
        

    return 0;
}