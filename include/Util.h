#pragma once

#include "syati.h"

class StarPointerOnOffController {
public:
    void incModeCounter(void *pHost, s32 mode);
};

namespace MR {
    void startStarPointerMode1PInvalid2PValid(void *pHost);
}