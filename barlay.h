#ifndef BARLAY_H
#define BARLAY_H

class barlay
{
private:
    const int buyPrice = 2;
    int barlayPrice = 2;        // product price
    int breedingTime = 20;      // breeding time =  20 second
    int penaltyTime = 10;       // penalty  time =  5 second

public:
    int getBuyPrice();
    int getBarlayPrice();
    int getBreedingTime();

    void decreaseBreedingTime();
    void decreasePenaltyTime();
    void decreaseBarlayPrice();

    int getPenaltyTime();

    void resetPenaltyTime();
};

#endif // BARLAY_H
