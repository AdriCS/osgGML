#include "GraphVisitor.h"

#include "DebugUtils.h"
#include "GmlOptions.h"
#include "GmlOptionsIO.h"

#include <cassert>
#include <iostream>

namespace osgGML {
	GraphVisitor::GraphVisitor()
	{}

	GraphVisitor::~GraphVisitor()
	{}

	void GraphVisitor::setOptions( GmlOptions* goptions ) {
		assert( goptions );
		options = goptions;
	}

	void GraphVisitor::visitFrom(
		osg::Node& root,
		std::ostream& out
	) {
		setTraversalMode( TRAVERSE_ALL_CHILDREN );
		
		root.accept( *this );
		
		out << "graph [" << std::endl;
		out << options->globalOptions() << std::endl;
		out << nodes.str() << edges.str() << std::endl;
		out << "]" << std::endl;
		
		nodes.clear();
		edges.clear();
		visited.clear();
	}
	
	void GraphVisitor::apply( osg::Node& node ) {
        DebugUtils::print( " APPLY NODE" );

		int id( -1 );
		if( getOrCreateId( &node, id ) ) {
			handle( node, id );
			handleAndTraverse( node, id );
		}
	}
	
	void GraphVisitor::apply( osg::Geode& geode ) {
        DebugUtils::print( " APPLY GEODE" );

		int id( -1 );
		if( getOrCreateId( &geode, id ) ) {
			handle( geode, id );
			handleAndTraverse( geode, id );
			
			for( unsigned int i( 0 ); i < geode.getNumDrawables(); ++i ) {
				osg::Drawable* drawable = geode.getDrawable( i );
				int id_child( -1 );
				if( getOrCreateId( drawable, id_child ) ) {
					handle( *drawable, id_child );
					osg::StateSet* ss = drawable->getStateSet();
					if( ss ) {
						int id_ss( -1 );
						
						if( getOrCreateId( ss, id_ss) ) {
							handle( *ss, id_ss );
						}
						handle( *drawable, *ss, id_child, id_ss );
					}
				}
				handle( geode, *drawable, id, id_child );
			}
		}		
	}
	
	void GraphVisitor::apply( osg::Group& group ) {
		std::cout << " APPLY GROUP" << std::endl;
		int id( -1 );
		
		if( getOrCreateId( &group, id) ) {
			handle( group, id );
			handleAndTraverse( group, id );
			
			
			for( unsigned int i( 0 ); i < group.getNumChildren(); ++i ) {
				osg::Node* child = group.getChild( i );
				int id_child( -1 );
				getOrCreateId( child, id_child );
				handle( group, *child, id, id_child );
			}
		}
	}

	void GraphVisitor::handleAndTraverse(
		osg::Node& node,
		const int id
	) {
		const osg::observer_ptr<osg::StateSet> ss = node.getStateSet();
		if( ss.valid() ) {
			int id_ss( -1 );
			if( getOrCreateId( ss.get(), id_ss ) ) {
				handle( *ss, id_ss );
			}
			handle( node, *ss, id, id_ss );
		}
		traverse( node );
	}
	
	void GraphVisitor::handle(
		osg::Node& node,
		const int id
	) {
		std::cout << " HANDLE NODE" << std::endl;
		std::string label( "Node" );
		if( !node.getName().empty() ) {
			label += "|";
			label += node.getName();
		}
		const Topology& topo = options->graphicOptions().getTopology( "Node" );
		drawNode( id, label, topo );
	}
	void GraphVisitor::handle(
		osg::Geode& node,
		const int id
	) {
		std::string label( node.className() );
		if( !node.getName().empty() ) {
			label += "|";
			label += node.getName();
		}
		const Topology& topo = options->graphicOptions().getTopology( node.className() );
		drawNode( id, label, topo );
	}
	void GraphVisitor::handle(
		osg::Group& node,
		const int id
	) {
		std::string label( node.className() );
		if( !node.getName().empty() ) {
			label += "|";
			label += node.getName();
		}
		const Topology& topo = options->graphicOptions().getTopology( node.className() );
		drawNode( id, label, topo );		
	}
	void GraphVisitor::handle(
		osg::StateSet& ss,
		const int id
	) {
		std::cout << " HANDLE SSET" << std::endl;
		std::string label( ss.className() );
		
		if( !ss.getName().empty() ) {
			label += "|";
			label += ss.getName();
		}
		const Topology& topo = options->graphicOptions().getTopology( ss.className() );
		drawNode( id, label, topo );
	}
	
	void GraphVisitor::handle(
		osg::Drawable& drawable,
		const int id
	) {
		std::cout << " HANDLE DRAW" << std::endl;
		std::string label( drawable.className() );
		
		if( !drawable.getName().empty() ) {
			label += "|";
			label += drawable.getName();
		}
		const Topology& topo = options->graphicOptions().getTopology( drawable.className() );
		drawNode( id, label, topo );
	}
	
	/**/
	void GraphVisitor::handle(
		osg::Node& node,
		osg::StateSet& ss,
		const int from,
		const int to
	) {
		const Topology& topo = options->graphicOptions().getTopology( ss.className() );
		drawEdge( from, to, topo );
	}
	
	void GraphVisitor::handle(
		osg::Group& parent,
		osg::Node& child,
		const int from,
		const int to
	) {
		const Topology& topo = options->graphicOptions().getTopology( child.className() );
		drawEdge( from, to, topo );		
	}
	
	void GraphVisitor::handle(
		osg::Geode& parent,
		osg::Drawable& child,
		const int from,
		const int to
	) {
		const Topology& topo = options->graphicOptions().getTopology( child.className() );
		drawEdge( from, to, topo );		
	}
	void GraphVisitor::handle(
		osg::Drawable& parent,
		osg::StateSet& child,
		const int from,
		const int to
	) {
		const Topology& topo = options->graphicOptions().getTopology( child.className() );
		drawEdge( from, to, topo );		
	}	
	/**/
	
	void GraphVisitor::drawNode(
		const int id,
		const std::string& label,
		const Topology& top
	) {
		nodes << "\tnode [\n";
		nodes << "\t\tid " << id << '\n';
		nodes << "\t\tlabel \"" << label << "\"\n";
		nodes << "\t\tgraphics [\n";
		nodes << "\t\t\ttype \"" << top.getBox() << "\"\n";
		nodes << "\t\t\tfill \"" << top.getFill() << "\"\n";
		nodes << "\t\t\toutline \"" << top.getOutline() << "\"\n";
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
		edges << "\t\t\ttype \"" << top.getEdge() << "\"\n";
		edges << "\t\t]\n";
		edges << "\t]\n";
	}
	bool GraphVisitor::getOrCreateId(
		osg::Object* obj,
		int &id
	) {
		assert( obj );
		VisitedMap::iterator it = visited.find( obj );
		if ( it != visited.end() ) {
			id = it->second;
			return false;
		}
		id = visited.size();
		visited[ obj ] = id;
		return true;
	}
}
