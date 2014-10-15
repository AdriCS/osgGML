#include "GmlOptions.h"

#include <iostream>

int main( int argc, char** argv ) {
	osgGML::GmlOptions::Ptr options = new osgGML::GmlOptions;
	std::cout << "Global, version/creator: "
			  << options->globalOptions().getVersion()
			  << " / " << options->globalOptions().getCreator()
			  << std::endl
	;
	
	const osgGML::GraphicOptions& graphics = options->graphicOptions();
	const osgGML::Topology& deftop = graphics.getDefault();
	std::cout << "Default topo: " << deftop.getBox() << ", "
			  << deftop.getEdge() << ", " << deftop.getFill()
			  << ", " << deftop.getOutline()
			  << std::endl
    ;
	osgGML::Topology topo = graphics.getTopology( "StateSet" );
	std::cout << "StateSet topo: " << topo.getBox() << ", "
			  << topo.getEdge() << ", " << topo.getFill()
			  << ", " << topo.getOutline()
			  << std::endl
    ;
	topo = graphics.getTopology( "Geode" );
	std::cout << "Geode topo: " << topo.getBox() << ", "
			  << topo.getEdge() << ", " << topo.getFill()
			  << ", " << topo.getOutline()
			  << std::endl
    ;
	topo = graphics.getTopology( "Unknown" );
	std::cout << "Unknown topo: " << topo.getBox() << ", "
			  << topo.getEdge() << ", " << topo.getFill()
			  << ", " << topo.getOutline()
			  << std::endl
    ;
	
	return 0;
}