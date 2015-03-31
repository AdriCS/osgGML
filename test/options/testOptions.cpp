#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Options

#include "GmlOptions.h"

#include "boost/test/unit_test.hpp"

/**
* \brief Simple test to check how Boost.Test works.
* \todo  Complete the test cases.
* \todo  Add more test cases.
*/
BOOST_FIXTURE_TEST_SUITE(Options, osgGML::GmlOptions)

BOOST_AUTO_TEST_CASE(DefaultGlobalOptions)
{
	const osgGML::GlobalOptions& gopts = globalOptions();
	
	BOOST_CHECK(gopts.hasCreator());
	BOOST_CHECK_EQUAL(gopts.getVersion(), 1);
	BOOST_CHECK_EQUAL(gopts.isDirected(), true);
	
	// Just to see what happens with BOOST_CHECK when it's false.
	// BOOST_CHECK(gopts.hasComment());
}

BOOST_AUTO_TEST_CASE(DefaultGraphicsOptions)
{
  const osgGML::GraphicOptions& gropts = graphicOptions();

  BOOST_CHECK(gropts.hasTopology("Drawable"));
  
  const osgGML::Topology& topo = gropts.getTopology("StateSet");
  BOOST_CHECK_EQUAL(topo.getEdge(), "dashed");
}

BOOST_AUTO_TEST_CASE(Setters)
{
	osgGML::GlobalOptions gopts = globalOptions();
  gopts.setGmlVersion(777);
  BOOST_CHECK_EQUAL(gopts.getVersion(), 777);
  
  // More to come.
  
}

BOOST_AUTO_TEST_SUITE_END()
