#pragma once

#define DO_API(a, r, n, p) extern r(*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC
