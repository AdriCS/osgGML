#include <cstdlib>
#include <iostream>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include "osgGA/GUIEventHandler"
#include "osgViewer/Viewer"
#include "osgViewer/ViewerEventHandlers"

#include "ReaderWriterGML.h"

class Picker: public osgGA::GUIEventHandler {
public:
	Picker() : osgGA::GUIEventHandler() {}
	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa ) {
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>( &aa );

		if( !viewer ) {
			return false;
		}
		
		switch( ea.getEventType() ) {
			case osgGA::GUIEventAdapter::KEYUP:
				if( osgGA::GUIEventAdapter::KEY_A == ea.getKey() ) {
				     osgViewer::Viewer::Cameras cameras;
					viewer->getCameras( cameras );
					
					osgDB::writeNodeFile( *( cameras[ 0 ] ), "out.gml" );
				}
				return true;
				break;
			default:
				break;
		}
		return false;
	}
protected:
	~Picker(){}
};

int main( int argc, char** argv ) {
	osgDB::Registry::instance()->addReaderWriter( new ReaderWriterGML );
	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow( 100, 100, 400, 400 );

	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile( "cessna.osg" );
	if( !scene.valid() ) {
		std::cerr << "NO LOADED MODEL\n";
		return EXIT_FAILURE;
	}
	viewer.addEventHandler( new osgViewer::WindowSizeHandler );
	viewer.addEventHandler( new Picker );
	viewer.setSceneData( scene );
	
	return viewer.run();
}