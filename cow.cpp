#include "cow.h"

int cow::getBuyPrice()
{
    return buyPrice;
}

int cow::getMeatPrice()
{
    return meatPrice;
}

int cow::getMilkPrice()
{
    return milkPrice;
}

int cow::getBreedingTime()
{
    return breedingTime;
}

int cow::getPenaltyTime()
{
    return penaltyTime;
}
void cow::decreaseBreedingTime()
{
    breedingTime--;
}
void cow::decreasePenaltyTime()
{
    penaltyTime--;
}
void cow::decreaseMilkPrice()
{
    milkPrice--;
}
void cow::resetPenaltyTime()
{
    penaltyTime = 3;
}
