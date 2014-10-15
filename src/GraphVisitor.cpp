#include "GraphVisitor.h"

#include "GmlOptions.h"

#include <cassert>

namespace osgGML {
	GraphVisitor::GraphVisitor()
	{}

	GraphVisitor::~GraphVisitor()
	{}

	void GraphVisitor::setOptions( GmlOptions* goptions ) {
		assert( goptions.valid() );
		options = goptions;
	}

	void GraphVisitor::visitFrom(
		const osg::Node& root,
		std::ostream& out
	) {
		setTraversalMode( osg::Object::TRAVERSE_ALL_CHILDREN );
		
		root.accept( *this );
		
		out << "graph [" << std::endl;
		out << options.globalOptions() << std::endl;
		out << nodes.str() << edges.str() << std::endl;
		out << "]" << std::endl;
		
		nodes.clear();
		edges.clear();
		visited.clear();
	}
	
	void GraphVisitor::apply( osg::Node& node ) {
		int id( -1 );
		if( getOrCreateId( &node, id ) {
			
		}
	}

	void GraphVisitor::drawNode(
		const int id,
		const std::string& label,
		const Topology& top
	) {
		nodes << "\tnode [\n";
		nodes << "\t\tid " << id << '\n';
		nodes << "\t\tlabel " << label << '\n';
		nodes << "\t\tgraphics [\n";
		nodes << "\t\t\ttype " << top.getBox() << '\n';
		nodes << "\t\t\tfill " << top.getFill() << '\n';
		nodes << "\t\t\toutline " << top.getOutline() << '\n';
		nodes << "\t\t]\n";
		nodes << "\t]\n";
	}

	void GraphVisitor::drawEdge(
		const int from,
		const int to,
		const Topology& top
	) {
		edges << "\tedge [\n";
		edges << "\t\tsource " << from << '\n';
		edges << "\t\ttarget " << to << '\n';
		edges << "\t\tgraphic [\n";
		edges << "\t\t\ttype " << top.getEdge() << '\n';
		edges << "\t\t]\n";
		edges << "\t]\n";
	}
	bool GraphVisitor::getOrCreateId(
		osg::Object* object,
		int &id
	) {
		assert( obj );
		VisitedMap::iterator it = visited.find( obj );
		if ( it != visited.end() ) {
			id = it->second;
			return false;
		}
		id = visited.size();
		visited[ object ] = id;
		return true;
	}
}