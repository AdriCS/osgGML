#ifndef __GMLOPTIONS_H__
#define __GMLOPTIONS_H__

/*!
* \todo String check. Always Latin-1 !!!
*/

#include "Setup.h"

#include <map>
#include <string>

#include <osgDB/Options>

namespace osgGML {
	/// \todo For now, supports only 1 graph.
	class GlobalOptions {
	public:
		GlobalOptions(
		) : 
			creator( "OSG GML Plugin" ),
			comment( "" ),
			version( 1 ),
			directed( true )
		{}

		GlobalOptions(
			const std::string& c,
			const int v,
			const bool d
		) :
			creator( c ),
			comment( "" ),
			version( v ),
			directed( d )
		{}
		
		bool hasCreator() const {
			return !getCreator().empty();
		}
		const std::string& getCreator() const {
			return creator;
		}
		bool hasComment() const {
			return !getComment().empty();
		}
		const std::string& getComment() const {
			return comment;
		}
		int getVersion() const {
			return version;
		}
		bool isDirected() const {
			return directed;
		}
		
		void setGmlVersion( const int v ) {
			version = v;
		}
		void setDirected( const bool d ) {
			directed = d;
		}
		
		bool setCreator( const std::string& cre );
		bool setComment( const std::string& co );
		
		// friend std::ostream& operator<<(
			// std::ostream& out,
			// const GlobalOptions& go
		// );
	private:
		std::string creator;
		std::string comment;
		int         version;
		bool        directed;
	};
		
	class Topology {
	public:
		enum BoxType {
			Rectangle = 0,
			Oval
		};
		enum EdgeType {
			Dashed = 0,
			Line
		};
		enum Colour {
			Black = 0,
			Blue,
			Green,
			Red,
			White
		};
	public:	
		Topology(
		) : 
			box( Rectangle ),
			edge( Line ),
			fill( White ),
			outline( Black )
		{}
		
		Topology(
			const BoxType b,
			const EdgeType e = Line,
			const Colour f = White,
			const Colour o = Black
		) :
			box( b ),
			edge( e ),
			fill( f ),
			outline( o )
		{}
		
		std::string getBox() const;
		std::string getEdge() const;
		std::string getFill() const;
		std::string getOutline() const;
		
		void setBox( const BoxType b ) {
			box = b;
		}
		void setEdge( const EdgeType e ) {
			edge = e;
		}
		void setFill( const Colour c ) {
			fill = c;
		}
		void setOutline( const Colour c ) {
			outline = c;
		}
	private:
		std::string colourToString( const Colour c ) const;
	private:
		BoxType  box;
		EdgeType edge;
		Colour fill;
		Colour outline;
	};

	class GraphicOptions {
	public:
		typedef std::map<std::string, Topology> Topologies;
		
		GraphicOptions();
		
		void addTopology(
			const std::string& name,
			const Topology& topology
		);
		
		bool hasTopology( const std::string& name ) const;
		
		const Topology& getTopology( const std::string& name ) const;
		
		const Topology& getDefault() const;
	// private:
		// GraphicOptions( const GraphicOptions& go );
		// GraphicOptions& operator=( const GraphicOptions& go );
#ifndef USE_LAMBDAS
		void addDefaultTopology()  DEPRECATED;
		void addDrawableTopology() DEPRECATED;
		void addGeodeTopology()    DEPRECATED;
		void addStateSetTopology() DEPRECATED;
#endif		
	private:
		// Special topologies.
		// Object name, Topology for object.
		// I. e: Geode, {Solid box, dashed edge, red fill }
		Topologies objectOpts;
	};

	class GmlOptions: public osgDB::Options {
	public:
		typedef osg::ref_ptr<GmlOptions> Ptr;
		// META_Object( osgGML, GmlOptions );
		GmlOptions();

		const GlobalOptions& globalOptions() const {
			return globalOpts;
		}
		const GraphicOptions& graphicOptions() const {
			return graphicOpts;
		}
	protected:
		~GmlOptions();
	private:
		GmlOptions& operator=( const GmlOptions& opts );
	private:
		GlobalOptions   globalOpts;
		GraphicOptions graphicOpts;
	};
}

#endif
