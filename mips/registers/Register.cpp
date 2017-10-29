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

#include <mips/registers/Register.hpp>

#include <cstdlib>

namespace MIPS {
namespace registers {

Register::Register()
    : m_forceConstant(false),
      m_registerValue(std::rand()),
      m_name(),
      m_type(),
      m_filled(false)
{
}

Register::Register(const RegisterType type)
    : m_forceConstant(false),
      m_registerValue(std::rand()),
      m_name(),
      m_type(type),
      m_filled(false)
{
}

Register::Register(const RegisterType type, const std::string name)
    : m_forceConstant(false),
      m_registerValue(std::rand()),
      m_name(name),
      m_type(type),
      m_filled(false)
{
}

Register::Register(const Register& other)
    : m_forceConstant(other.isForced()),
      m_registerValue(other.getRegisterValue()),
      m_name(other.getName()),
      m_type(other.getType()),
      m_filled(other.isFilled())
{
}

Register::Register(const RegisterType type, const std::string name, const RegisterValue value)
    : m_forceConstant(false),
      m_registerValue(value),
      m_name(name),
      m_type(type),
      m_filled(false)
{
}

Register::Register(const RegisterType type, const std::string name, const RegisterValue value, const bool forceConstant)
    : m_forceConstant(forceConstant),
      m_registerValue(value),
      m_name(name),
      m_type(type),
      m_filled(false)
{
}

void Register::setRegisterValue(const RegisterValue value)
{
    if (!m_forceConstant)
    {
        m_registerValue = value;
        m_filled = true;
    }
}

void Register::clearRegisterValue()
{
    m_filled = false;
}

} // namespace registers
} // namespace MIPS