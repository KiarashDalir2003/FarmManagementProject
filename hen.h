#ifndef HEN_H
#define HEN_H

class hen
{
private:
    const int buyPrice = 3;
    const int meatPrice = 2;
    const int eggPrice = 3;         // product price
    const int breedingTime = 20;    // breeding time =  20 second
    const int penaltyTime = 5;      // penalty  time = 5 second

public:
    int getBuyPrice();
    int getMeatPrice();
    int getEggPrice();
    int getBreedingTime();
    int getPenaltyTime();
};


#endif // HEN_H
