#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Options

#include "GmlOptions.h"

#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(DefaultOptions)
{
	BOOST_CHECK(1 == 1);
}
