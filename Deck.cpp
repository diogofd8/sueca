#include "Deck.h"

Deck::Deck ()
{
    auto i = 0;
    for (auto s = 0; s < 4; ++s)
    {
        for (auto r = 0; r < 10; ++r)
        {
            element[i].setCard(s, r);
            ++i;
        }
    }
}

Deck::~Deck ()
{

}

void Deck::shuffleDeck (int &times)
{
    for (auto i = 0; i < times; ++i)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(element.begin(), element.end(), std::default_random_engine(seed));
    }
    return;
}

void Deck::printDeck ()
{
    for (auto c = 0; c < element.size(); ++c)
    {
        std::cout << "card\t(" << c << ")\t";
        element[c].printCard(); 
        std::cout << std::endl;
    }
    return;
}

Card& Deck::getDeckCard (int &index)
{
    return element[index];
}

Card& Deck::getDeckCard (int index)
{
    return element[index];
}