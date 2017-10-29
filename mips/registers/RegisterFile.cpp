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

 #include <mips/common/utils/filter.hpp>
 #include <mips/registers/RegisterFile.hpp>
 #include <cassert>

namespace MIPS {
namespace registers {

using namespace MIPS::Utils;

const static int NUM_RETURN_REGISTER = 2;
const static int NUM_ARGUMENT_REGISTER = 4;
const static int NUM_TEMPORARY_REGISTER = 8;
const static int NUM_SAVED_REGISTER = 8;
const static int NUM_TEMPORARY_REGISTER_2 = 8;
const static int NUM_KERNEL_REGISTER = 2;
    
RegisterFile::RegisterFile()
{
    int fillLevel = 0;
    m_registers[0] = Register(RegisterType::kRegisterTypeZero, "$zero", 0, true);
    m_registers[1] = Register(RegisterType::kRegisterTypePseudoInstruction, "$at");
    fillLevel = 2;

    for (auto i=0; i < NUM_RETURN_REGISTER; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeReturn, "$v" + std::to_string(i));
    }
    fillLevel += NUM_RETURN_REGISTER;

    for (auto i=0; i < NUM_ARGUMENT_REGISTER; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeArgument, "$a" + std::to_string(i));
    }
    fillLevel += NUM_ARGUMENT_REGISTER;
    
    for (auto i=0; i < NUM_TEMPORARY_REGISTER; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeTemporary, "$t" + std::to_string(i));
    }
    fillLevel += NUM_TEMPORARY_REGISTER;
    
    for (auto i=0; i < NUM_SAVED_REGISTER; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeSaved, "$s" + std::to_string(i));
    }
    fillLevel += NUM_SAVED_REGISTER;
    
    for (auto i=0; i < NUM_TEMPORARY_REGISTER_2; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeTemporary, "$t" + std::to_string(i + NUM_TEMPORARY_REGISTER));
    }
    fillLevel += NUM_TEMPORARY_REGISTER_2;
    
    for (auto i=0; i < NUM_KERNEL_REGISTER; ++i)
    {
        m_registers[i+fillLevel] = Register(RegisterType::kRegisterTypeKernel, "$k" + std::to_string(i));
    }
    fillLevel += NUM_KERNEL_REGISTER;
    
    m_registers[fillLevel] = Register(RegisterType::kRegisterTypeGlobalPointer, "$gp");
    m_registers[fillLevel+1] = Register(RegisterType::kRegisterTypeStackPointer, "$sp");
    m_registers[fillLevel+2] = Register(RegisterType::kRegisterTypeFramePointer, "$fp");
    m_registers[fillLevel+3] = Register(RegisterType::kRegisterTypeReturnAddress, "$ra");
    fillLevel += 4;
    assert(fillLevel == m_registers.size());
}

const RegisterValue RegisterFile::getRegisterValue(const std::string& name) const
{
    Register reg = getRegisterByName(name);
    return reg.getRegisterValue();
}

const RegisterValue RegisterFile::getRegisterValue(const RegisterIndex& index) const
{
    Register reg = getRegisterByIndex(index);
    return reg.getRegisterValue();
}

void RegisterFile::setRegisterValue(const std::string& name, const RegisterValue value)
{
    Register reg = getRegisterByName(name);
    reg.setRegisterValue(value);
}

void RegisterFile::setRegisterValue(const RegisterIndex& index, const RegisterValue value)
{
    Register reg = getRegisterByIndex(index);
    reg.setRegisterValue(value);
}

Register RegisterFile::getRegisterByName(const std::string& name) const
{
    for (auto reg : m_registers)
    {
        if (reg.getName() == name)
            return reg;
    }
    assert(0); // No such register name exists
}

} // namespace registers
} // namespace MIPS