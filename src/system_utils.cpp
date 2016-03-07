#include "system_utils.h"

std::string getMachineType ()
{
	std::string machineType = "";
	struct utsname buf;
	int ret;
	ret =  uname(&buf);
	if (!ret) {
		machineType = buf.machine;
	}
	return machineType;
}
// vim:set ts=2 :
