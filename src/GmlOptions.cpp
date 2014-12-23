#include "GmlOptions.h"

#include <cstdio>

namespace osgGML {
	// GlobalOptions

	bool GlobalOptions::setCreator( const std::string& cre ) {
		// Check Latin1 str
		creator = cre;
		return true;
	}

	bool GlobalOptions::setComment( const std::string& co ) {
		// Check Latin1 str
		comment = co;
		return true;
	}
	/*****************************************************/

	// Topology

	std::string Topology::getBox() const {
		std::string toret;

		switch( box ) {
			case Rectangle:
			default:
				toret = "rectangle";
				break;
			case Oval:
				toret = "oval";
				break;
		}
		return toret;
	}

	std::string Topology::getEdge() const {
		std::string toret;

		switch( edge ) {
			case Dashed:
				toret = "dashed";
				break;
			case Line:
			default:
				toret = "line";
				break;
		}
		return toret;
	}

	std::string Topology::getFill() const {
		return colourToString( fill );
	}
	std::string Topology::getOutline() const {
		return colourToString( outline );
	}

	std::string Topology::colourToString( const Colour c ) const {
	#if 0
		std::string toret;

		switch( c ) {
			case Black:
				toret = "black";
				break;
			case Blue:
				toret = "blue";
				break;
			case Green:
				toret = "green";
				break;
			case Red:
				toret = "red";
				break;
			case White:
			default:
				toret = "white";
				break;
		}
		return toret;
	#endif
		char tmp[ 8 ];

		switch( c ) {
			case Black:
				std::snprintf( tmp, sizeof( tmp ), "#%02x%02x%02x", 0, 0, 0 );
				break;
			case Blue:
				std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", 0, 0, 255 );
				break;
			case Green:
				std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", 0, 255, 0 );
				break;
			case White:
			default:
				std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", 255, 255, 255 );
				break;
		}
		return std::string( tmp );
	}

	/*****************************************************/

	// GraphicOptions

	GraphicOptions::GraphicOptions(
	) :
	   objectOpts()
	{
#if defined(USE_LAMBDAS)
		addTopology(
			"Default",
			[]() -> Topology {
				Topology topo;
				return topo;
			}()
		);
		addTopology(
			"Drawable",
			[]() -> Topology {
				Topology topo;
				topo.setOutline( Topology::Blue );
				return topo;
			}()
		);
		addTopology(
			"Geode",
			[]() -> Topology {
				Topology topo;
				topo.setOutline( Topology::Red );
				return topo;
			}()
		);
		addTopology(
			"StateSet",
			[]() -> Topology {
				Topology topo( 
					Topology::Oval,
					Topology::Dashed
				);
				topo.setOutline( Topology::Green );
				return topo;
			}()
		);
#else
	addDefaultTopology();
	addDrawableTopology();
	addGeodeTopology();
	addStateSetTopology();
#endif
	}

	void GraphicOptions::addTopology(
		const std::string& name,
		const Topology& topology
	) {
		objectOpts[ name ] = topology;
	}

	bool GraphicOptions::hasTopology( const std::string& name ) const {
		Topologies::const_iterator it = objectOpts.find( name );
		
		return ( objectOpts.end() != it ) ? true : false;
	}

	// const Topology& GraphicOptions::getTopology( const std::string& name ) const {
		// return objectOpts[ name ];
	// }
	
	const Topology& GraphicOptions::getDefault() const {
		return getTopology( "Default" );
	}
	
	const Topology& GraphicOptions::getTopology( const std::string& name ) const {
		Topologies::const_iterator it = objectOpts.find( name );
		if( objectOpts.end() != it ) {
			return it->second;
		} else {
			return getDefault();
		}
	}
	
#ifndef USE_LAMBDAS
	void GraphicOptions::addDefaultTopology() {
		Topology topo;
		addTopology( "Default", topo );
	}
	void GraphicOptions::addDrawableTopology() {
		Topology topo;
		topo.setOutline( Topology::Blue );
		addTopology( "Drawable", topo );
	}

	void GraphicOptions::addGeodeTopology() {
		Topology topo;
		topo.setOutline( Topology::Red );
		addTopology( "Geode", topo );
	}

	void GraphicOptions::addStateSetTopology() {
		Topology topo(
			Topology::Oval,
			Topology::Dashed
		);
		topo.setOutline( Topology::Green );
		addTopology( "StateSet", topo );
	}
#endif
	/*****************************************************/

	// GmlOptions

	GmlOptions::GmlOptions(
	) :
		globalOpts(),
		graphicOpts()
	{}

	GmlOptions::~GmlOptions()
	{}
}
