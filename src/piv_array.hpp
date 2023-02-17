﻿/*
 * 火山视窗 - 数组辅助增强
 * 作者: Xelloss
 * 网站: https://piv.ink
 * 邮箱: xelloss@vip.qq.com
 * 版本: 2023/02/14
 */

#ifndef _PIV_ARRAY_HPP
#define _PIV_ARRAY_HPP

#if _MSVC_LANG < 201703L
#error 数组P(数组辅助增强)需要 C++17 或更高标准,请使用 Visual Studio 2017 以上版本的编译器
#endif

// 包含火山视窗基本类,它在火山里的包含顺序比较靠前(全局-110)
#ifndef __VOL_BASE_H__
#include <sys/base/libs/win_base/vol_base.h>
#endif

#include <type_traits>

namespace piv
{
    namespace arr
    {
        // 数组_求和
        template <typename R, typename T>
        R Sum(const T &array)
        {
            INT_P Count = array.data().GetCount();
            assert(Count > 0);

            R result;
            if constexpr (std::is_same_v<R, CVolString>)
            {
                CVolString str;
                str.AddText(array.data().GetAt(0));
                for (INT_P i = 1; i < Count; i++)
                {
                    str.AddText(array.data().GetAt(i));
                }
                return str;
            }
            else
            {
                result = array.data().GetAt(0);
                for (INT_P i = 1; i < Count; i++)
                {
                    result = result + array.data().GetAt(i);
                }
                return result;
            }
        }

        // 数组_求最大值
        template <typename R, typename T>
        R MaxImum(const T &array)
        {
            INT_P Count = array.data().GetCount();
            assert(Count > 0);

            R result;
            if constexpr (std::is_same_v<R, CVolString>)
            {
                const TCHAR *str = array.data().GetAt(0);
                for (INT_P i = 1; i < Count; i++)
                {
                    if (_wcsicmp(str, array.data().GetAt(i)) < 0)
                    {
                        str = array.data().GetAt(i);
                    }
                }
                return CVolString(str);
            }
            else
            {
                result = array.data().GetAt(0);
                for (INT_P i = 1; i < Count; i++)
                {
                    result = (std::max)(result, array.data().GetAt(i));
                }
                return result;
            }
        }

        // 数组_求最小值
        template <typename R, typename T>
        R MinImum(const T &array)
        {
            INT_P Count = array.data().GetCount();
            assert(Count > 0);

            R result;
            if constexpr (std::is_same_v<R, CVolString>)
            {
                const TCHAR *str = array.data().GetAt(0);
                for (INT_P i = 1; i < Count; i++)
                {
                    if (_wcsicmp(str, array.data().GetAt(i)) > 0)
                    {
                        str = array.data().GetAt(i);
                    }
                }
                return CVolString(str);
            }
            else
            {
                result = array.data().GetAt(0);
                for (INT_P i = 1; i < Count; i++)
                {
                    result = (std::min)(result, array.data().GetAt(i));
                }
                return result;
            }
        }

        // 展示数组
        template <typename T>
        CVolString FormatArray(const T &arr)
        {
            using EleType = std::remove_reference_t<decltype(arr.data().GetAt(0))>;
            CVolString result;
            result.AddChar(L'{');

            bool emit = false;
            INT_P Count = arr.data().GetCount();

            if constexpr (std::is_same_v<EleType, const TCHAR *>) // 文本数组类
            {
                for (INT_P i = 0; i < Count; i++)
                {
                    if (emit)
                    {
                        result.AddText(L", ");
                    }
                    else
                    {
                        emit = true;
                    }
                    result.AddChar(L'\"');
                    result.AddText(arr.data().GetAt(i));
                    result.AddChar(L'\"');
                }
            }
            else
            {
                for (INT_P i = 0; i < Count; i++)
                {
                    if (emit)
                    {
                        result.AddText(L", ");
                    }
                    else
                    {
                        emit = true;
                    }
                    result.AddText(arr.data().GetAt(i));
                }
            }
            result.AddChar(L'}');
            return result;
        }

        // 创建数组类
        template <typename R, typename... Ts>
        constexpr R CreateArray(Ts &&...args)
        {
            R result;
            if constexpr (std::is_same_v<R, CVolObjectArray>)
            {
                (result.Add(args, NULL), ...);
            }
            else
            {
                (result.data().Add(args), ...);
            }
            return result;
        }

        // 连续加入成员
        template <typename T, typename... Ts>
        void AddManyValues(T &array, Ts &&...args)
        {
            if constexpr (std::is_same_v<T, CVolObjectArray>)
            {
                (array.Add(args, NULL), ...);
            }
            else
            {
                (array.data().Add(args), ...);
            }
        }

        // 取数组前面
        template <typename T>
        T GetArrayFront(const T &array, const INT_P &num)
        {
            INT_P Count = 0;
            if constexpr (std::is_same_v<T, CVolObjectArray>)
            {
                Count = array.GetCount();
            }
            else
            {
                Count = array.data().GetCount();
            }
            if (Count == 0)
            {
                return T{};
            }
            if (num >= Count)
            {
                return array;
            }

            T result;
            for (INT_P i = 0; i < num; i++)
            {
                if constexpr (std::is_same_v<T, CVolObjectArray>)
                {
                    result.Add(array.GetAt(i), NULL);
                }
                else
                {
                    result.data().Add(array.data().GetAt(i));
                }
            }
            return result;
        }

        // 取数组后面
        template <typename T>
        T GetArrayBack(const T &array, const INT_P &num)
        {
            INT_P Count = 0;
            if constexpr (std::is_same_v<T, CVolObjectArray>)
            {
                Count = array.GetCount();
            }
            else
            {
                Count = array.data().GetCount();
            }
            if (Count == 0)
            {
                return T{};
            }
            if (num >= Count)
            {
                return array;
            }

            T result;
            for (INT_P i = Count - num; i < Count; i++)
            {
                if constexpr (std::is_same_v<T, CVolObjectArray>)
                {
                    result.Add(array.GetAt(i), NULL);
                }
                else
                {
                    result.data().Add(array.data().GetAt(i));
                }
            }
            return result;
        }

        // 取对象数组数据
        template <typename T>
        CVolMem SaveObjArrToData(const T &array)
        {
            if constexpr (std::is_same_v<T, CVolObjectArray>)
            {
                CVolMem memData;
                INT Count = static_cast<INT>(array.GetCount());
                memData.AddInt(Count); // 数组成员数
                for (INT i = 0; i < Count; i++)
                {
                    CVolMemoryOutputStream memStream;
                    array.GetAt(i).VolSaveIntoStream(memStream);
                    CVolMem bin = memStream.GetBin(CVolMem());
                    memData.AddInt(static_cast<INT>(bin.GetSize())); // 成员的数据长度
                    memData.Append(bin);                // 成员的内容数据
                }
                return memData;
            }
            return CVolMem();
        }

        // 置对象数组数据
        template <typename T, typename M>
        BOOL LoadObjArrData(T &array, CVolMem &memData, M &member)
        {
            if constexpr (std::is_same_v<T, CVolObjectArray>)
            {
                array.RemoveAll();
                INT_P DataSize = memData.GetSize();
                if (DataSize < 8)
                {
                    return FALSE;
                }
                INT nCount = memData.Get_INT(0);
                INT_P MemberSize, npOffset = 4;
                for (INT i = 0; i < nCount; i++)
                {
                    member.ResetObject();
                    CVolMemoryInputStream memStream;
                    MemberSize = (INT_P)memData.Get_INT(npOffset);
                    npOffset += 4;
                    if (DataSize < MemberSize + npOffset)
                    {
                        array.RemoveAll();
                        return FALSE;
                    }
                    memStream.ResetMemory(memData.GetBinMid(npOffset, MemberSize));
                    member.VolLoadFromStream(memStream);
                    array.Add(member, NULL);
                    npOffset += MemberSize;
                }
                return TRUE;
            }
            return FALSE;
        }

    } // namespace arr
} // namespace piv

#endif // _PIV_ARRAY_HPP
