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


#include <mips/common/utils/logging/MIPSLogging.hpp>
#include <mips/common/utils/logging/LogSystemInterface.hpp>

#include <stack>
#include <memory>


namespace MIPS {
namespace Utils {
namespace Logging {

static std::shared_ptr<LogSystemInterface> MIPSLogSystem(nullptr);
static std::shared_ptr<LogSystemInterface> OldLogger(nullptr);

void InitializeMIPSLogging(const std::shared_ptr<LogSystemInterface> &logSystem) {
    MIPSLogSystem = logSystem;
}

void ShutdownMIPSLogging(void) {
    InitializeMIPSLogging(nullptr);
}

LogSystemInterface *GetLogSystem() {
    return MIPSLogSystem.get();
}

void PushLogger(const std::shared_ptr<LogSystemInterface> &logSystem)
{
    OldLogger = MIPSLogSystem;
    MIPSLogSystem = logSystem;
}

void PopLogger()
{
    MIPSLogSystem = OldLogger;
    OldLogger = nullptr;
}

} // namespace Logging
} // namespace Utils
} // namespace MIPS