#ifndef __GMLOPTIONSIO_H__
#define __GMLOPTIONSIO_H__

#include "GmlOptions.h"

#include <ostream>

namespace osgGML {
	std::ostream& operator<<(
		std::ostream& out,
		const GlobalOptions& go
	);
}

#endif
