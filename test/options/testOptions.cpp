#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Options

#include "GmlOptions.h"

#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(DefaultOptions)
{
	osgGML::GmlOptions::Ptr opts = new osgGML::GmlOptions;
	osgGML::GlobalOptions gopts = opts->globalOptions();
	
	BOOST_CHECK(gopts.hasCreator());
	BOOST_CHECK(1 == gopts.getVersion());
	BOOST_CHECK(true == gopts.isDirected());
	
	// Just to see what happens with BOOST_CHECK when it's false.
	BOOST_CHECK(gopts.hasComment());
}