#ifndef BARLAY_H
#define BARLAY_H

class barlay
{
private:
    const int buyPrice = 2;
    const int barlayPrice = 2;        // product price
    const int breedingTime = 20;      // breeding time =  20 second
    const int penaltyTime = 10;       // penalty  time =  5 second

public:
    int getBuyPrice();
    int getBarlayPrice();
    int getBreedingTime();
    int getPenaltyTime();
};

#endif // BARLAY_H
