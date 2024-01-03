#ifndef WHEAT_H
#define WHEAT_H

class wheat
{
private:
    const int buyPrice = 2;
    const int wheatPrice = 3;        // product price
    const int breedingTime = 25;     // breeding time =  20 second
    const int penaltyTime = 12;      // penalty  time =  5 second

public:
    int getBuyPrice();
    int getWheatPrice();
    int getBreedingTime();
    int getPenaltyTime();
};

#endif // WHEAT_H
