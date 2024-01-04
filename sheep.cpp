#include "sheep.h"

int sheep::getBuyPrice()
{
    return buyPrice;
}

int sheep::getMeatPrice()
{
    return meatPrice;
}

int sheep::getMilkPrice()
{
    return milkPrice;
}

int sheep::getBreedingTime()
{
    return breedingTime;
}

int sheep::getPenaltyTime()
{
    return penaltyTime;
}
void sheep::decreaseBreedingTime()
{
    breedingTime--;
}
void sheep::decreasePenaltyTime()
{
    penaltyTime--;
}
void sheep::decreaseMilkPrice()
{
    milkPrice--;
}
void sheep::resetPenaltyTime()
{
    penaltyTime = 4;
}
