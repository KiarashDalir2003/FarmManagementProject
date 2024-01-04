#include "wheat.h"

int wheat::getBuyPrice()
{
    return buyPrice;
}

int wheat::getWheatPrice()
{
    return wheatPrice;
}

int wheat::getBreedingTime()
{
    return breedingTime;
}

int wheat::getPenaltyTime()
{
    return penaltyTime;
}

void wheat::decreaseBreedingTime()
{
    breedingTime--;
}

void wheat::decreasePenaltyTime()
{
    penaltyTime--;
}

void wheat::decreaseWheatPrice()
{
    wheatPrice--;
}

void wheat::resetPenaltyTime()
{
    penaltyTime = 12;
}
