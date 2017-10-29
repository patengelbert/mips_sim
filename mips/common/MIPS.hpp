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

#include <memory>
#include <functional>

#include <MIPS/common/utils/logging/LogLevel.hpp>
#include <MIPS/common/utils/logging/LogSystemInterface.hpp>

namespace MIPS
{
static const char* DEFAULT_LOG_PREFIX = "mips_";

/**
 * SDK wide options for logging
 */
struct LoggingOptions
{
    LoggingOptions() : logLevel(MIPS::Utils::Logging::LogLevel::Off), defaultLogPrefix(DEFAULT_LOG_PREFIX)
    { }

    /**
     * Defaults to Off, if this is set to something else, then logging will be turned on and logLevel will be passed to the logger
     */
    MIPS::Utils::Logging::LogLevel logLevel;

    /**
     * Defaults to aws_sdk_. This will only be used if the default logger is used.
     */
    const char* defaultLogPrefix;

    /**
     * Defaults to empty, if logLevel has been set and this field is empty, then the default log interface will be used.
     * otherwise, we will call this closure to create a logger
     */
        std::function<std::shared_ptr<MIPS::Utils::Logging::LogSystemInterface>()> logger_create_fn;
};

struct CPUOptions
{
    /**
     * CPU wide options for logging
     */
    LoggingOptions loggingOptions;

};

/*
    * Initialize SDK wide state for the SDK. This method must be called before doing anything else with this library.
    *
    * Common Recipes:
    *
    * Just use defaults:
    *
    * SDKOptions options;
    * Aws::InitAPI(options);
    * .....
    * Aws::ShutdownAPI(options);
    *
    * Turn logging on using the default logger:
    *
    * SDKOptions options;
    * options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    * Aws::InitAPI(options);
    * .....
    * Aws::ShutdownAPI(options);
    *
    * Install custom memory manager:
    *
    * MyMemoryManager memoryManager;
    *
    * SDKOptions options;
    * options.memoryManagementOptions.memoryManager = &memoryManager;
    * Aws::InitAPI(options);
    * .....
    * Aws::ShutdownAPI(options);
    *
    * Override default http client factory
    *
    * SDKOptions options;
    * options.httpOptions.httpClientFactory_create_fn = [](){ return Aws::MakeShared<MyCustomHttpClientFactory>("ALLOC_TAG", arg1); };
    * Aws::InitAPI(options);
    * .....
    * Aws::ShutdownAPI(options);
    */
void InitCPU(const CPUOptions& options);

/**
 * Shutdown SDK wide state for the SDK. This method must be called when you are finished using the SDK.
 * Do not call any other SDK methods after calling ShutdownAPI.
 */
void ShutdownCPU(const CPUOptions& options);
}