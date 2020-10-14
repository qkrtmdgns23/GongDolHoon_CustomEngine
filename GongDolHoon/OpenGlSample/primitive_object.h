#ifndef GDH_ENGINE_PRIMITIVE_OBJECT_H
#define GDH_ENGINE_PRIMITIVE_OBJECT_H

// custom library
#include "object.h"

namespace gdh_engine {
	namespace object {
		class PrimitiveObject : public Object
		{
		public:
			virtual ~PrimitiveObject() {}
		};
	}	// namespace object
}	// namespace gdh_engine


#endif // GDH_ENGINE_PRIMITIVE_OBJECT_H