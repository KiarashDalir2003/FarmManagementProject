#ifndef SHEEP_H
#define SHEEP_H

class sheep
{
private:
    const int buyPrice = 5;
    const int meatPrice = 4;
    const int milkPrice = 3;        // product price
    const int breedingTime = 15;    // breeding time =  20 second
    const int penaltyTime = 4;      // penalty  time = 5 second

public:
    int getBuyPrice();
    int getMeatPrice();
    int getMilkPrice();
    int getBreedingTime();
    int getPenaltyTime();
};

#endif // SHEEP_H
