#include "ReaderWriterGML.h"

#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
// #include <osgDB/ReaderWriter>

#include "GmlOptions.h"
#include "GraphVisitor.h"

	const char* ReaderWriterGML::className() const {
		return "GML Writer";
	}
	bool ReaderWriterGML::acceptsExtension( const std::string& extension ) const {
		return osgDB::equalCaseInsensitive( extension, "gml" );
	}
	osgDB::ReaderWriter::WriteResult ReaderWriterGML::writeNode(
		const osg::Node& node,
		const std::string& filename,
		const osgDB::Options* options
	) const {
		const std::string ext = osgDB::getFileExtension( filename );
		if( !acceptsExtension( ext ) ) {
			return osgDB::ReaderWriter::WriteResult::FILE_NOT_HANDLED;
		}

		osgDB::ofstream out( filename.c_str(), std::ios::out );
		if( !out ) {
			return osgDB::ReaderWriter::WriteResult::ERROR_IN_WRITING_FILE;
		}
		
		// check opts;
		osgGML::GmlOptions::Ptr goptions = NULL;
		if(
			osgGML::GmlOptions* opts = dynamic_cast<osgGML::GmlOptions*>(
				const_cast<osgDB::Options*>( options ) )
		) {
			goptions = new osgGML::GmlOptions( *opts );
		} else {
			goptions = new osgGML::GmlOptions;
		}

		osgGML::GraphVisitor vis;
		vis.setOptions( goptions.get() );
		vis.visitFrom( *const_cast<osg::Node*>( &node ), out );

		return osgDB::ReaderWriter::WriteResult(
			osgDB::ReaderWriter::WriteResult::FILE_SAVED
		);
	}
	
	REGISTER_OSGPLUGIN(gml, ReaderWriterGML)