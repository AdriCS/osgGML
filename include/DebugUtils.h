#ifndef __DEBUGUTILS_H__
#define __DEBUGUTILS_H__

#include <cassert>
#include <iostream>

namespace DebugUtils {
    template<class T>
    void print( const T& msg,
                std::ostream& ost = std::cout,
                const bool flush = true
    ) {
#if defined(DO_DEBUG)
        assert( false );
        ost << msg << '\n';
        if( flush ) {
            ost << std::flush;
        }
#else
		static_cast<void>(msg);
		static_cast<void>(ost);
		static_cast<void>(flush);
#endif
    }
}

#endif
