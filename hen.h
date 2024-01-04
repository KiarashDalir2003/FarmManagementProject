#ifndef HEN_H
#define HEN_H

class hen
{
private:
    const int buyPrice = 3;
    const int meatPrice = 2;
     int eggPrice = 3;         // product price
     int breedingTime = 20;    // breeding time =  20 second
     int penaltyTime = 5;      // penalty  time = 5 second

public:
    int getBuyPrice();
    int getMeatPrice();
    int getEggPrice();
    int getBreedingTime();
    void decreaseBreedingTime();
    void decreasePenaltyTime();
    void decreaseEggPrice();
    int getPenaltyTime();
    void resetPenaltyTime();
};


#endif // HEN_H
