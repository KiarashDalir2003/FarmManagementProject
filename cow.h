#ifndef COW_H
#define COW_H

class cow
{
private:
    const int buyPrice = 7;
    const int meatPrice = 6;
    const int milkPrice = 5;        // product price
    const int breedingTime = 20;    // breeding time =  20 second
    const int penaltyTime = 3;      // penalty  time = 5 second

public:
    int getBuyPrice();
    int getMeatPrice();
    int getMilkPrice();
    int getBreedingTime();
    int getPenaltyTime();
};

#endif // COW_H
