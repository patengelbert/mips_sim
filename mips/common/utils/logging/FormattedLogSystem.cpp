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

#include <mips/common/utils/logging/FormattedLogSystem.hpp>

#include <mips/common/utils/DateTime.hpp>
#include <mips/common/utils/Array.hpp>

#include <fstream>
#include <cstdarg>
#include <cstdio>
#include <thread>

namespace MIPS {
namespace Utils {
namespace Logging {

static std::string CreateLogPrefixLine(LogLevel logLevel, const char* tag)
{
    std::stringstream ss;

    switch(logLevel)
    {
        case LogLevel::Error:
            ss << "[ERROR] ";
            break;

        case LogLevel::Fatal:
            ss << "[FATAL] ";
            break;

        case LogLevel::Warn:
            ss << "[WARN] ";
            break;

        case LogLevel::Info:
            ss << "[INFO] ";
            break;

        case LogLevel::Debug:
            ss << "[DEBUG] ";
            break;

        case LogLevel::Trace:
            ss << "[TRACE] ";
            break;

        default:
            ss << "[UNKOWN] ";
            break;
    }

    ss << DateTime::CalculateLocalTimestampAsString("%Y-%m-%d %H:%M:%S") << " " << tag << " [" << std::this_thread::get_id() << "] ";

    return ss.str();
}

FormattedLogSystem::FormattedLogSystem(LogLevel logLevel) :
    m_logLevel(logLevel)
{
}

void FormattedLogSystem::Log(LogLevel logLevel, const char* tag, const char* formatStr, ...)
{
    std::stringstream ss;
    ss << CreateLogPrefixLine(logLevel, tag);

    std::va_list args;
    va_start(args, formatStr);

    va_list tmp_args; //unfortunately you cannot consume a va_list twice
    va_copy(tmp_args, args); //so we have to copy it
    #ifdef WIN32
        const int requiredLength = _vscprintf(formatStr, tmp_args) + 1;
    #else
        const int requiredLength = vsnprintf(nullptr, 0, formatStr, tmp_args) + 1;
    #endif
    va_end(tmp_args);

    Array<char> outputBuff(requiredLength);
    #ifdef WIN32
        vsnprintf_s(outputBuff.GetUnderlyingData(), requiredLength, _TRUNCATE, formatStr, args);
    #else
        vsnprintf(outputBuff.GetUnderlyingData(), requiredLength, formatStr, args);
    #endif // WIN32

    ss << outputBuff.GetUnderlyingData() << std::endl;  

    ProcessFormattedStatement(ss.str());

    va_end(args);
}

void FormattedLogSystem::LogStream(LogLevel logLevel, const char* tag, const std::ostringstream &message_stream)
{
    std::stringstream ss;
    ss << CreateLogPrefixLine(logLevel, tag) << message_stream.rdbuf()->str() << std::endl;

    ProcessFormattedStatement(ss.str());
}

} // namespace Logging
} // namespace Utils
} // namespace MIPS