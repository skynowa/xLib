/**
 * \file  Stl.h
 * \brief STL all headers
 *
 * Used in:
 *
 * - https://github.com/skynowa/xLib/blob/master/Include/xLib/Core/Stl.h
 * - https://github.com/skynowa/CppTest/blob/master/Stl.h
 */


#pragma once

// C
#ifndef _GLIBCXX_NO_ASSERT
    #include <cassert>
#endif

#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if (__cplusplus >= 201103L) // xLANG_CPP11
    #include <ccomplex>
    #include <cfenv>
    #include <cinttypes>

    #if defined(__APPLE__)
        //
    #else
        #include <cstdalign>
        #include <cuchar>
    #endif

    #include <cstdbool>
    #include <cstdint>
    #include <ctgmath>
    #include <cwchar>
    #include <cwctype>
#endif

// C++
#include <algorithm>
#include <functional>

#include <bitset>
#include <complex>

#include <exception>
#include <stdexcept>

/// RAT
#if 1
	#include <iostream>
	#include <fstream>
#else
	#include <ios>
	#include <iosfwd>	// TODO: use only <iosfwd>
	#include <iostream>
	#include <istream>
	#include <ostream>
	#include <sstream>
	#include <fstream>
	#include <streambuf>
#endif

#include <iomanip>

#include <iterator>
#include <limits>
#include <utility>
#include <locale>
#include <memory>
#include <new>
#include <numeric>
#include <typeinfo>

#include <string>
#include <valarray>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>

// C++11
#if (__cplusplus >= 201103L) // xLANG_CPP11
    #include <array>
    #include <chrono>
    #include <codecvt>
    #include <forward_list>
    #include <initializer_list>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <tuple>
    #include <typeindex>
    #include <type_traits>
    #include <unordered_map>
    #include <unordered_set>

    // MT / IPC
    #include <atomic>
    #include <condition_variable>
    #include <future>
    #include <mutex>
    #include <thread>
#endif

#if (__cplusplus >= 201402L) // xLANG_CPP14
    // MT / IPC
    #include <shared_mutex>
#endif

#if (__cplusplus >= 201703L) // xLANG_CPP17
    #include <any>
    #include <optional>
    #include <variant>
    #include <string_view>
    #include <charconv>
    #include <filesystem>
    // TODO: #include <execution>
#endif

#if (__cplusplus >= 202002L) // xLANG_CPP20
    #include <bit>
    #include <compare>
    #include <concepts>
    #include <coroutine>
    #include <numbers>
    #include <ranges>
    #include <span>
    #include <stop_token>
    #include <syncstream>
    #include <version>
#endif
