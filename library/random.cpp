//
//  random.cpp
//  sj
//
//  Created by Mann, Justin on 2/4/17.
//  Copyright © 2017 Mann, Justin. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>

extern "C" __int64_t random_nextInt() {
    return (__uint64_t)rand() << 32 | (__uint64_t)rand();
}
