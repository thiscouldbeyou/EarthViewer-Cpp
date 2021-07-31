#ifndef __EVSYSTEM__
#define __EVSYSTEM__

#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

using Timestep = float;

using Size = std::size_t;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

#endif