/**
 *   Copyright 2017 Patrick Engelbert
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <mips/common/utils/logging/LogLevel.hpp>

#include <cassert>

namespace MIPS {
namespace Utils {
namespace Logging {

std::string GetLogLevelName(LogLevel logLevel) 
{ 
	switch (logLevel)
	{
	case LogLevel::Fatal:
		return "FATAL";
	case LogLevel::Error:
		return "ERROR";
	case LogLevel::Warn:
		return "WARN";
	case LogLevel::Info:
		return "INFO";
	case LogLevel::Debug:
		return "DEBUG";
	case LogLevel::Trace:
		return "TRACE";
	default:
		assert(0);
		return "";
	}   
}

} // namespace Logging
} // namespace Utils
} // namespace MIPS