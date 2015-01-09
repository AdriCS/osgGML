#ifndef __SETUP_H__
#define __SETUP_H__

#if __cplusplus <= 199711L && defined( __GXX_EXPERIMENTAL_CXX0X__ )
	#warning USING C++0X
	#define USE_LAMBDAS
#endif

#ifdef __GNUC__
    #define DEPRECATED __attribute__ ( ( deprecated) )
#endif

#endif
