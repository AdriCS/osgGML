#include "GmlOptions.h"

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
	
	std::ostream& operator<<(
		std::ostream& out,
		const GlobalOptions& go
	) {
		if( go.hasCreator() ) {
			out << "\tCreator " << go.getCreator() << '\n';
		}
		if( go.hasComment() ) {
			out << "\tcomment " << go.getComment() << '\n';
		}
		out << "\tVersion " << go.getVersion() << '\n';
		out << "\tdirected " << ( go.isDirected() ? 1 : 0 ) << '\n';
		
		return out;
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
				topo.setOutline( Blue );
				return topo;
			}()
		);
		addTopology(
			"Geode",
			[]() -> Topology {
				Topology topo;
				topo.setOutline( Red );
				return topo;
			}()
		);
		addTopology(
			"StateSet",
			[]() -> Topology {
				Topology topo( 
					Oval,
					Dashed
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