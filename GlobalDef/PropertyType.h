/*****************************************************************/ /**
 * \file   PropertyType.h
 * \brief  属性类型枚举
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

namespace xStudio
{
    enum PropertyType
    {
        PropertyType_UnKnown    = 0,
        PropertyType_Bool       = 1, //_b
        PropertyType_Int        = 2, //_i
        PropertyType_UInt       = 3, //_u
        PropertyType_UInt64     = 4, //_u64
        PropertyType_Float      = 5, //_f
        PropertyType_Double     = 6, //_d
        PropertyType_String     = 7, //_s
        PropertyType_Vector3    = 8, //_v3
        PropertyType_Color      = 9, //_c
        PropertyType_MObjectPtr = 10 //MObject指针 _o
    };
} // namespace xStudio
