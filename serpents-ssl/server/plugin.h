#ifndef PLUGIN_H_
#define PLUGIN_H_
#define PLUGIN_FUNC extern 'C' GUSLIB_EXPORT_SYMBOL

#include "guslib\system\dynamiclibmanager.h"
#include <string>

namespace serpents{
	class IPlugin{
	public:
		IPlugin(){}
		virtual ~IPlugin(){}
		virtual const std::string& getName() const = 0;
		virtual void install() = 0;
		virtual void initialise() = 0;
		virtual void shutdown() = 0;
		virtual void uninstall() = 0;
	};
}
#endif