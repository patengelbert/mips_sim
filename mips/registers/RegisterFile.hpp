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
#include <mips/registers/Register.hpp>

#include <array>
#include <vector>
#include <cassert>

namespace MIPS {
namespace registers {

const static int REGISTER_FILE_SIZE = 32; // DO NOT CHANGE

typedef std::array<Register, REGISTER_FILE_SIZE> RegisterArray;
typedef std::vector<Register> FilteredRegisterArray;

typedef RegisterArray::size_type RegisterIndex;

class RegisterAccessor
{
public:

    enum AccessorType : int
    {
        kAccessorTypeName = 0,
        kAccessorTypeIndex
    };

    RegisterAccessor(const std::string name) : m_name(name), m_index(-1){};
    RegisterAccessor(const RegisterIndex index) : m_name(), m_index(index){};

    const std::string getName() const
    {
        return m_name;
    };

    const RegisterIndex getIndex() const
    {
        return m_index;
    };

    const AccessorType type() const
    {
        if (m_index >= 0)
            return AccessorType::kAccessorTypeIndex;
        else if (!m_name.empty())
            return AccessorType::kAccessorTypeName;
        else
            assert(0); // No accessor type set

    };

private:
    const std::string m_name;
    const RegisterIndex m_index;
};

class RegisterFile : public MIPSComponent
{
public:
    RegisterFile();
    virtual ~RegisterFile(){};

    const RegisterValue getRegisterValue(const std::string& name) const;
    const RegisterValue getRegisterValue(const RegisterIndex& index) const;

    void setRegisterValue(const std::string& name, const RegisterValue value);
    void setRegisterValue(const RegisterIndex& index, const RegisterValue value);

protected:
    Register getRegisterByName(const std::string& name) const;
    inline Register getRegisterByIndex(const RegisterIndex& index) const { assert(index < REGISTER_FILE_SIZE); return m_registers[index]; };

private:
    RegisterArray m_registers;
};

} // namespace registers
} // namespace MIPS