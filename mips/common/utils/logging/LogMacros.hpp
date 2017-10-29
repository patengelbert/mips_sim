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

#pragma once

#include <mips/common/utils/logging/LogLevel.hpp>
#include <mips/common/utils/logging/MIPSLogging.hpp>
#include <mips/common/utils/logging/LogSystemInterface.hpp>

// While macros are usually grotty, using them here lets us have a simple function call interface for logging that
//
//  (1) Can be compiled out completely, so you don't even have to pay the cost to check the log level (which will be a virtual function call and a std::atomic<> read) if you don't want any MIPS logging
//  (2) If you use logging and the log statement doesn't pass the conditional log filter level, not only do you not pay the cost of building the log string, you don't pay the cost for allocating or
//      getting any of the values used in building the log string, as they're in a scope (if-statement) that never gets entered.

#ifdef DISABLE_MIPS_LOGGING

#define MIPS_LOG(level, tag, ...) 
#define MIPS_LOG_FATAL(tag, ...) 
#define MIPS_LOG_ERROR(tag, ...) 
#define MIPS_LOG_WARN(tag, ...) 
#define MIPS_LOG_INFO(tag, ...) 
#define MIPS_LOG_DEBUG(tag, ...) 
#define MIPS_LOG_TRACE(tag, ...) 

#define MIPS_LOGSTREAM(level, tag, streamExpression) 
#define MIPS_LOGSTREAM_FATAL(tag, streamExpression)
#define MIPS_LOGSTREAM_ERROR(tag, streamExpression)
#define MIPS_LOGSTREAM_WARN(tag, streamExpression)
#define MIPS_LOGSTREAM_INFO(tag, streamExpression)
#define MIPS_LOGSTREAM_DEBUG(tag, streamExpression)
#define MIPS_LOGSTREAM_TRACE(tag, streamExpression)

#else

#define MIPS_LOG(level, tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= level ) \
        { \
            logSystem->Log(level, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_FATAL(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Fatal ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Fatal, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_ERROR(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Error ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Error, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_WARN(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Warn ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Warn, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_INFO(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Info ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Info, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_DEBUG(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Debug ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Debug, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOG_TRACE(tag, ...) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Trace ) \
        { \
            logSystem->Log(MIPS::Utils::Logging::LogLevel::Trace, tag, __VA_ARGS__); \
        } \
    }

#define MIPS_LOGSTREAM(level, tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= level ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( logLevel, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_FATAL(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Fatal ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Fatal, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_ERROR(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Error ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Error, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_WARN(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Warn ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Warn, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_INFO(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Info ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Info, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_DEBUG(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Debug ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Debug, tag, logStream ); \
        } \
    }

#define MIPS_LOGSTREAM_TRACE(tag, streamExpression) \
    { \
        MIPS::Utils::Logging::LogSystemInterface* logSystem = MIPS::Utils::Logging::GetLogSystem(); \
        if ( logSystem && logSystem->GetLogLevel() >= MIPS::Utils::Logging::LogLevel::Trace ) \
        { \
            MIPS::OStringStream logStream; \
            logStream << streamExpression; \
            logSystem->LogStream( MIPS::Utils::Logging::LogLevel::Trace, tag, logStream ); \
        } \
    }

#endif // DISABLE_MIPS_LOGGING