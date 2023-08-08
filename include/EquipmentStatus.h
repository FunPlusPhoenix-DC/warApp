#ifndef _EQUIPMENTSTATUS_H_

#define _EQUIPMENTSTATUS_H_

#endif

#include "pch.h"

#ifdef _cplusplus

extern "C"{

#endif  //begin to define

typedef struct EquipmentStruct
{
    float fEquipmentProperty;

    float fUpperSentence;

    float fLowerSentence;

    float fStrengthenLevel;

    float fGem;

    float fDisasterStone;
}*LPEQUIPMENTSTRUCT;

typedef struct EquipmentExtraAbility{
    bool bIsBelongToSkills;

    char p_szArmsSpecialDescribe[256];

    bool bIsFrozenAdditionDmg;

    float fBleedingDmg;
}*LPEQUIPMENTEXTRAABILITY;


class WARAPPDLL_API EquipmentProperties{
    private:

    char p_PATH_EquipmentImg[MAX_PATH];

    char p_szEquipmentName[64];

    public:

    EquipmentProperties();

    ~EquipmentProperties();

    void SetEquipmentImgPath(const char* szPath);

    char* GetEquipmentImgPath();

    void SetEquipmentName(const char* szName);

    char* GetEquipmentName();

    LPEQUIPMENTSTRUCT lpEquipmentStruct;

    LPEQUIPMENTEXTRAABILITY lpEquipmentExtraAbility;
};

#ifdef _cplusplus

}

#endif