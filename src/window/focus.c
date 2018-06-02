#include "focus.h"

#include "../components/types.h"
#include "../components/xwindowdata.h"

const uint64_t LOCK = COMPONENT_FOCUS | COMPONENT_XWIN;

void focus_update(float dt, Vector* keys, Vector* floatData, Vector* xWindowData) {
    size_t j = 0;
    size_t k = 0;
    for(size_t i = 0; i < vector_size(keys); i++) {
        uint64_t key = (uint64_t)vector_get(keys, i);
        if((key & LOCK) == LOCK) {
            printf("MAKE FOCUS\n");
        }

        j += key & COMPONENT_FOCUS ? 1 : 0;
        k += key & COMPONENT_XWIN ? 1 : 0;
    }
}
