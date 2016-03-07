#include "error_treat.h"

RunTimeErrorWithErrno::RunTimeErrorWithErrno(const std::string& msg) throw()
	: std::runtime_error(msg + std::string(": ") + strerror(errno))
{
}
RunTimeErrorWithErrno::RunTimeErrorWithErrno(const std::string& msg, int e) throw()
	: std::runtime_error(msg + std::string(": ") + strerror(e))
{
}
// vim:set ts=2 :
