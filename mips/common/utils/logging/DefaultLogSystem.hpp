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

#include <mips/common/utils/logging/FormattedLogSystem.hpp>
#include <mips/common/utils/logging/LogLevel.hpp>

#include <queue>
#include <thread>
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace MIPS {
namespace Utils {
namespace Logging {
/**
 * Default behavior logger. It has a background thread that reads a log queue and prints the messages
 * out to file as quickly as possible.  This implementation also rolls the file every hour.
 */
class DefaultLogSystem : public FormattedLogSystem
{
public:
    using Base = FormattedLogSystem;

    /**
     * Initialize the logging system to write to the supplied logfile output. Creates logging thread on construction.
     */
    DefaultLogSystem(LogLevel logLevel, const std::shared_ptr<std::ostream>& logFile);
    /**
     * Initialize the logging system to write to a computed file path filenamePrefix + "timestamp.log". Creates logging thread
     * on construction.
     */
    DefaultLogSystem(LogLevel logLevel, const std::string& filenamePrefix);
    virtual ~DefaultLogSystem();

    /**
     * Structure containing semaphores, queue etc... 
     */
    struct LogSynchronizationData
    {
    public:
        LogSynchronizationData() : m_stopLogging(false) {}

        std::mutex m_logQueueMutex;
        std::condition_variable m_queueSignal;
        std::queue<std::string> m_queuedLogMessages;
        std::atomic<bool> m_stopLogging;

    private:
        LogSynchronizationData(const LogSynchronizationData& rhs) = delete;
        LogSynchronizationData& operator =(const LogSynchronizationData& rhs) = delete;
    };

protected:
    /**
     * Pushes log onto the queue and notifies the background thread.
     */
    virtual void ProcessFormattedStatement(std::string&& statement) override;

private:
    DefaultLogSystem(const DefaultLogSystem& rhs) = delete;
    DefaultLogSystem& operator =(const DefaultLogSystem& rhs) = delete;

    LogSynchronizationData m_syncData;

    std::thread m_loggingThread;
};

} // namespace Logging
} // namespace Utils
} // namespace MIPS