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



#include <mips/common/utils/logging/DefaultLogSystem.hpp>

#include <mips/common/utils/DateTime.hpp>

#include <fstream>

namespace MIPS {
namespace Utils {
namespace Logging {

static const char* AllocationTag = "DefaultLogSystem";

static std::shared_ptr<std::ofstream> MakeDefaultLogFile(const std::string filenamePrefix)
{
    std::string newFileName = filenamePrefix + DateTime::CalculateLocalTimestampAsString("%Y-%m-%d-%H") + ".log";
    return std::make_shared<std::ofstream>(AllocationTag, newFileName.c_str(), std::ofstream::out | std::ofstream::app);
}

static void LogThread(DefaultLogSystem::LogSynchronizationData* syncData, const std::shared_ptr<std::ostream>& logFile, const std::string& filenamePrefix, bool rollLog)
{
    bool done = false;
    int32_t lastRolledHour = DateTime::CalculateCurrentHour();
    std::shared_ptr<std::ostream> log = logFile;

    while(!done)
    {
        std::unique_lock<std::mutex> locker(syncData->m_logQueueMutex);
        if(syncData->m_stopLogging.load() == false && syncData->m_queuedLogMessages.size() == 0)
        {
            syncData->m_queueSignal.wait(locker, [&](){ return syncData->m_stopLogging.load() == true || syncData->m_queuedLogMessages.size() > 0; } );
        }

        std::vector<std::string> messages;
        while(!syncData->m_queuedLogMessages.empty())
        {
            messages.push_back(syncData->m_queuedLogMessages.front());
            syncData->m_queuedLogMessages.pop();
        }

        done = syncData->m_stopLogging.load() && syncData->m_queuedLogMessages.size() == 0;
        locker.unlock();

        if(messages.size() > 0)
        {
            if (rollLog)
            {
                int32_t currentHour = DateTime::CalculateCurrentHour();
                if (currentHour != lastRolledHour)
                {
                    log = MakeDefaultLogFile(filenamePrefix);
                    lastRolledHour = currentHour;
                }
            }

            for (uint32_t i = 0; i < messages.size(); ++i)
            {
                (*log) << messages[i];
            }
            log->flush();
        }
    }
}

DefaultLogSystem::DefaultLogSystem(LogLevel logLevel, const std::shared_ptr<std::ostream>& logFile) :
    Base(logLevel),
    m_syncData(),
    m_loggingThread()
{
    m_loggingThread = std::thread(LogThread, &m_syncData, logFile, "", false);
}

DefaultLogSystem::DefaultLogSystem(LogLevel logLevel, const std::string& filenamePrefix) :
    Base(logLevel),
    m_syncData(),
    m_loggingThread()
{
    m_loggingThread = std::thread(LogThread, &m_syncData, MakeDefaultLogFile(filenamePrefix), filenamePrefix, true);
}

DefaultLogSystem::~DefaultLogSystem()
{
    {
        std::lock_guard<std::mutex> locker(m_syncData.m_logQueueMutex);
        m_syncData.m_stopLogging.store(true);
    }

    m_syncData.m_queueSignal.notify_one();

    m_loggingThread.join();
}

void DefaultLogSystem::ProcessFormattedStatement(std::string&& statement)
{
    {
        std::lock_guard<std::mutex> locker(m_syncData.m_logQueueMutex);
        m_syncData.m_queuedLogMessages.push(std::move(statement));
    }

    m_syncData.m_queueSignal.notify_one();
}

} // namespace Logging
} // namespace Utils
} // namespace MIPS