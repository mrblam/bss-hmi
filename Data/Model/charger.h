#ifndef CHARGER_H
#define CHARGER_H

#include "basemodel.h"

class Charger : public BaseModel
{
private:
    uint32_t input_power_state;
public:
    Charger();
};

#endif // CHARGER_H
