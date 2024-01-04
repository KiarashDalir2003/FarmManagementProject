#ifndef COW_H
#define COW_H

class cow
{
private:
    const int buyPrice = 7;
    const int meatPrice = 6;
     int milkPrice = 5;        // product price
     int breedingTime = 20;    // breeding time =  20 second
     int penaltyTime = 3;      // penalty  time = 5 second

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

#endif // COW_H
