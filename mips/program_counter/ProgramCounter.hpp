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

#include <mips/common/MIPSComponent.hpp>

#include <cstdint>

namespace MIPS {
namespace PC {

typedef uint32_t ProgramCounterValue;

class ProgramCounter : public MIPSComponent
{
public:
    
    inline const ProgramCounterValue getProgramCounter() const { return m_programCounter; };

    inline void setProgramCounter(const ProgramCounterValue programCounter) { m_programCounter = programCounter; }

    void increment();

    ProgramCounter();

    ProgramCounter(const ProgramCounter& other);

    virtual ~ProgramCounter(){};

private:
    ProgramCounterValue m_programCounter;
};

} // namespace PC
} // namespace MIPS
