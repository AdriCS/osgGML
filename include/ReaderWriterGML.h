#ifndef __READERWRITERGML_H__
#define __READERWRITERGML_H__

#include <osgDB/ReaderWriter>

class ReaderWriterGML: public osgDB::ReaderWriter {
public:
	virtual const char* className() const;
	virtual bool acceptsExtension( const std::string& extension ) const;
	virtual osgDB::ReaderWriter::WriteResult writeNode(
		const osg::Node& node,
		const std::string& filename,
		const osgDB::Options* options = NULL
	) const;
};

#endif