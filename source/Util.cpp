#include "Util.h"

extern "C" {
    StarPointerOnOffController* getStarPointerOnOffController__29unnamedStarPointerUtil_cppFv();
}

namespace MR {
    void startStarPointerMode1PInvalid2PValid(void *pHost) {
        getStarPointerOnOffController__29unnamedStarPointerUtil_cppFv()->incModeCounter(pHost, 9);
    }
}