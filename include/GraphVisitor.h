#ifndef __GRAPHVISITOR_H__
#define __GRAPHVISITOR_H__

#include <map>
#include <sstream>

#include <osg/Drawable>
#include <osg/Geode>
#include <osg/Group>
#include <osg/NodeVisitor>


namespace osgGML {
	class GmlOptions;
	class Topology;

	class GraphVisitor: public osg::NodeVisitor {
	public:
		typedef std::map<osg::Object*, int> VisitedMap;
		
		GraphVisitor();
		
		~GraphVisitor();
		
		void visitFrom(
			osg::Node& root,
			std::ostream& out
		);
		
		void setOptions( GmlOptions* goptions );
		
		virtual void apply( osg::Node& node );
		virtual void apply( osg::Geode& geode );
		virtual void apply( osg::Group& group );
	private:
		void handleAndTraverse(osg::Node& node, int id); //

		/* virtual */ void handle(osg::Node& node, int id); //
		/* virtual */ void handle(osg::Geode& node, int id);
		/* virtual */ void handle(osg::Group& node, int id);
		/* virtual */ void handle(osg::StateSet& stateset, int id);
		/* virtual */ void handle(osg::Drawable& drawable, int id);

		/* virtual */ void handle(osg::Node& node, osg::StateSet& stateset, const int from, const int to);
		/* virtual */ void handle(osg::Group& parent, osg::Node& child, const int from, const int to);
		/* virtual */ void handle(osg::Geode& geode, osg::Drawable& drawable, const int from, const int to);
		/* virtual */ void handle(osg::Drawable& drawable, osg::StateSet& stateset, const int from, const int to );
	
		void drawNode(
			const int id,
			const std::string& label,
			const Topology& top
			);
		void drawEdge(
			const int from,
			const int to,
			const Topology& top
		);
		bool getOrCreateId(
			osg::Object* obj,
			int& id
		);
	private:
		osg::ref_ptr<GmlOptions> options;
		std::stringstream nodes;
		std::stringstream edges;
		VisitedMap visited;
	};
}

#endif
