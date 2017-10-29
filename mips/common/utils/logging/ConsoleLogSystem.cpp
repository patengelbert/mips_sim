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


#include <mips/common/utils/logging/ConsoleLogSystem.hpp>

#include <iostream>
  
namespace MIPS  {
namespace Utils {
namespace Logging {
              
void ConsoleLogSystem::ProcessFormattedStatement(std::string&& statement)
{
    std::cout << statement;
}

} // namespace Logging
} // namespace Utils
} // namespace MIPS