#include "Util.h"

extern "C" {
    StarPointerOnOffController* __kAutoMap_8005BCB0(); // getStarPointerOnOffController__29@unnamed@StarPointerUtil_cpp@Fv
}

namespace MR {
    void startStarPointerMode1PInvalid2PValid(void *pHost) {
        __kAutoMap_8005BCB0()->incModeCounter(pHost, StarPointerMode_DemoWithStarPointer);
    }
}