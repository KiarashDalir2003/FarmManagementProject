#include "barlay.h"

int barlay::getBuyPrice()
{
    return buyPrice;
}

int barlay::getBarlayPrice()
{
    return barlayPrice;
}

int barlay::getBreedingTime()
{
    return breedingTime;
}

int barlay::getPenaltyTime()
{
    return penaltyTime;
}

void barlay::decreaseBreedingTime()
{
    breedingTime--;
}

void barlay::decreasePenaltyTime()
{
    penaltyTime--;
}
void barlay::decreaseBarlayPrice()
{
    barlayPrice--;
}

void barlay::resetPenaltyTime()
{
    penaltyTime = 10;
}
