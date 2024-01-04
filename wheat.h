#ifndef WHEAT_H
#define WHEAT_H

class wheat
{
private:
    const int buyPrice = 2;
    int wheatPrice = 3;        // product price
    int breedingTime = 25;     // breeding time =  20 second
    int penaltyTime = 12;      // penalty  time =  5 second

public:
    int getBuyPrice();
    int getWheatPrice();
    int getBreedingTime();

    void decreaseBreedingTime();
    void decreasePenaltyTime();
    void decreaseWheatPrice();

    int getPenaltyTime();

    void resetPenaltyTime();
};

#endif // WHEAT_H
