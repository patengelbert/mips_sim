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

namespace MIPS
{
namespace Utils
{
namespace Logging
{
class LogSystemInterface;

// Standard interface

/**
 * Call this at the beginning of your program, prior to any MIPS calls.
 */
void InitializeMIPSLogging(const std::shared_ptr<LogSystemInterface>& logSystem);

/**
 * Call this at the exit point of your program, after all calls have finished.
 */
void ShutdownMIPSLogging(void);

/**
 * Get currently configured log system instance.
 */
LogSystemInterface* GetLogSystem();

// Testing interface

/**
 * Replaces the current logger with a new one, while pushing the old one onto a 1-deep stack; primarily for testing
 */
void PushLogger(const std::shared_ptr<LogSystemInterface> &logSystem);

/**
 * Pops the logger off the logger stack and replaces the current logger with it.  Disables logging if the top logger is actually a nullptr
 */
void PopLogger();

} // namespace Logging
} // namespace Utils
} // namespace MIPS