#include "hen.h"

int hen::getBuyPrice()
{
    return buyPrice;
}

int hen::getMeatPrice()
{
    return meatPrice;
}

int hen::getEggPrice()
{
    return eggPrice;
}

int hen::getBreedingTime()
{
    return breedingTime;
}

int hen::getPenaltyTime()
{
    return penaltyTime;
}
void hen::decreaseBreedingTime()
{
    breedingTime--;
}
void hen::decreasePenaltyTime()
{
    penaltyTime--;
}
void hen::decreaseEggPrice()
{
    eggPrice--;
}
void hen::resetPenaltyTime()
{
    penaltyTime = 5;
}
