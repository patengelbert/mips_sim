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
#include <string>
#include <ostream>
#include <map>

namespace MIPS {
namespace registers {

typedef uint32_t RegisterValue;

enum RegisterType : int
{
    kRegisterTypeZero = 0,
    kRegisterTypePseudoInstruction,
    kRegisterTypeReturn,
    kRegisterTypeArgument,
    kRegisterTypeTemporary,
    kRegisterTypeSaved,
    kRegisterTypeKernel,
    kRegisterTypeGlobalPointer,
    kRegisterTypeStackPointer,
    kRegisterTypeFramePointer,
    kRegisterTypeReturnAddress
};

std::map<RegisterType, const char*> RegisterTypeMap;

class Register : public MIPSComponent
{
public:
    Register();
    Register(const RegisterType type);
    Register(const RegisterType type, const std::string name);
    Register(const Register& other);
    Register(const RegisterType type, const std::string name, const RegisterValue value);
    Register(const RegisterType type, const std::string name, const RegisterValue value, const bool forceConstant);

    virtual ~Register(){};

    inline const RegisterValue getRegisterValue() const { return m_registerValue; };

    void setRegisterValue(const RegisterValue value);

    void clearRegisterValue();

    inline const std::string getName() const { return m_name; };
    inline const RegisterType getType() const { return m_type; };

protected:
    inline const bool isForced() const { return m_forceConstant; };
    inline const bool isFilled() const { return m_filled; };

private:
    RegisterValue m_registerValue;
    bool m_forceConstant;
    std::string m_name;
    RegisterType m_type;
    bool m_filled;

};

std::ostream& operator<<(std::ostream& os, const RegisterType& type)
{
    const char* s;
#define PROCESS_VAL(p, v) case(p): s = v; break;
    switch(type){
        PROCESS_VAL(RegisterType::kRegisterTypeZero,                "ZERO");
        PROCESS_VAL(RegisterType::kRegisterTypePseudoInstruction,   "PSEUDO INSTRUCTION");
        PROCESS_VAL(RegisterType::kRegisterTypeReturn,              "RETURN VALUE");
        PROCESS_VAL(RegisterType::kRegisterTypeArgument,            "ARGUMENT");
        PROCESS_VAL(RegisterType::kRegisterTypeTemporary,           "TEMPORARY");
        PROCESS_VAL(RegisterType::kRegisterTypeSaved,               "SAVED");
        PROCESS_VAL(RegisterType::kRegisterTypeKernel,              "KERNEL");
        PROCESS_VAL(RegisterType::kRegisterTypeGlobalPointer,       "GLOBAL AREA POINTER");
        PROCESS_VAL(RegisterType::kRegisterTypeStackPointer,        "STACK POINTER");
        PROCESS_VAL(RegisterType::kRegisterTypeFramePointer,        "FRAME POINTER");
        PROCESS_VAL(RegisterType::kRegisterTypeReturnAddress,       "RETURN ADDRESS");
        default : s = "<UNKNOWN>"
    }
#undef PROCESS_VAL

    return os << s;
}

} // namespace registers
} // namespace MIPS