#ifndef ASSERT_EXTENSIONS_H
#define ASSERT_EXTENSIONS_H

#include <assert.h>

#define assert_equal(a, b) assert((a) == (b))
#define assert_not_equal(a, b) assert((a) != (b))

#endif