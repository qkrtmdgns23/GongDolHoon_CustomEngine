#ifndef GDH_ENGINE_ICOMPONENT_H
#define GDH_ENGINE_ICOMPONENT_H

namespace gdh_engine {
	namespace object
	{
		class IComponent {
		public:
			virtual ~IComponent() {}

			virtual void SetActive() = 0;
			virtual void SetUnActive() = 0;
		};
	}	// namespace object
}	// namespace gdh_engine

#endif // GDH_ENGINE_ICOMPONENT_H