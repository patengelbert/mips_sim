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

 #include <algorithm>

namespace MIPS {
namespace Utils {

template<typename C, typename T>
C filter(C inVec, function<bool(const T&)> predicate)
{
    C result;
    copy_if(inVec.begin(), inVec.end(), back_inserter(result), predicate);
    return result;
}

template<typename Cin, typename Cout, typename T>
Cout filter(Cin inVec, function<bool(const T&)> predicate)
{
    Cout result;
    copy_if(inVec.begin(), inVec.end(), back_inserter(result), predicate);
    return result;
}

} // namespace Utils
} // namespace MIPS