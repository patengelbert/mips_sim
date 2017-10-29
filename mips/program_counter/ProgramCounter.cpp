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

#include <mips/program_counter/ProgramCounter.hpp>

namespace MIPS {
namespace PC {

const static ProgramCounterValue PROGRAM_COUNTER_INCREMENT = 4;

ProgramCounter::ProgramCounter()
    : MIPSComponent(),
      m_programCounter(0)
{   
}

ProgramCounter::ProgramCounter(const ProgramCounter& other)
    : MIPSComponent(),
      m_programCounter(other.getProgramCounter())
{
}

void ProgramCounter::increment()
{
    m_programCounter += PROGRAM_COUNTER_INCREMENT;
}

} // namespace PC
} // namespace MIPS