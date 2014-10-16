#include "GmlOptionsIO.h"

namespace osgGML {
	/// \todo custom number of tabs. Custom streambuf class.
	std::ostream& operator<<(
		std::ostream& out,
		const GlobalOptions& go
	) {
		if( go.hasCreator() ) {
			out << "\tCreator \"" << go.getCreator() << "\"\n";
		}
		if( go.hasComment() ) {
			out << "\tcomment \"" << go.getComment() << "\"\n";
		}
		out << "\tVersion " << go.getVersion() << '\n';
		out << "\tdirected " << ( go.isDirected() ? 1 : 0 ) << '\n';
		
		return out;
	}
}