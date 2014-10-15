#ifndef __GRAPHVISITOR_H__
#define __GRAPHVISITOR_H__

#include <map>
#include <sstream>

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
			const osg::Node& root,
			std::ostream& out
		);
		
		void setOptions( GmlOptions* goptions );
		
		virtual void apply( osg::Node& node );
		virtual void apply( osg::Geode& geode );
		virtual void apply( osg::Group& group );
	private:
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
