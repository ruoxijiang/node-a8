//
// Created by weicheng qian on 2020/8/12.
//

#ifndef A8_DEBUG_HPP
#define A8_DEBUG_HPP

#include <assert.h>
#ifdef EDI_DEBUG
#define EdiAssert(e) \
    assert(e)
#else
#define EdiAssert(e)
#endif

#endif //A8_DEBUG_HPP
