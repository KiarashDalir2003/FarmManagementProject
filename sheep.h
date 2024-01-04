#ifndef SHEEP_H
#define SHEEP_H

class sheep
{
private:
    const int buyPrice = 5;
    const int meatPrice = 4;
    int milkPrice = 3;        // product price
    int breedingTime = 15;    // breeding time =  20 second
    int penaltyTime = 4;      // penalty  time = 5 second

public:
    int getBuyPrice();
    int getMeatPrice();
    int getMilkPrice();
    int getBreedingTime();
    void decreaseBreedingTime();
    void decreasePenaltyTime();
    void decreaseMilkPrice();
    int getPenaltyTime();
    void resetPenaltyTime();
};

#endif // SHEEP_H
