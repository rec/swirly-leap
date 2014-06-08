extern "C" {
#include "ext.h"
}

#include "MaxObject.h"

int C74_EXPORT main() {
    swirly::leap::registerMaxObject();
    return 0;
}
