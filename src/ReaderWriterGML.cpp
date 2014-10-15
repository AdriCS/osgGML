#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB/ReaderWriter>

#include "GmlOptions.h"
#include "GraphVisitor.h"

class ReaderWriterGML: public osgDB::ReaderWriter {
public:
	virtual const char* className() const {
		return "GML Writer";
	}
	virtual bool acceptsExtension( const std::string& extension ) const {
		return osgDB::equalCaseInsensitive( extension, "gml" );
	}
	virtual WriteResutl writeNode(
		const osg::Node& node,
		const std::string& filename,
		const osgDB::Options* = NULL
	) const {
		const std::string ext = osgDB::getFileExtension( filename );
		if( !acceptsExtension( ext ) ) {
			return osgDB::WriteResult::FILE_NOT_HANDLED;
		}

		osgDB::ofstream out( filename.c_str(), std::ios::out );
		if( !out ) {
			return osgDB::WriteResult::ERROR_IN_WRITING_FILE;
		}
		
		// check opts;
		osg::ref_ptr<osgGML::GmlOptions> goptions = NULL;
		if(
			osgGML::GmlOptions* opts = dynamic_cast<osgGML::GmlOptions*>(
				const_cast<osgDB::Options*>( options )
		) {
			goptions = new osgGML::GmlOptions( *options );
		} else {
			goptions = new osgGML::GmlOptions;
		}

		osgGML::GraphVisitor vis;
		vis.setOptions( goptions.get() );
		vis.visitFrom( node, out );

		return osgDB::WriteResult( osgDB::WriteResult::FILE_SAVED );
	}
};

REGISTER_OSGPLUGIN(gml, ReaderWriterGML)
