#ifndef HEROSTATUS_H_

#define HEROSTATUS_H_

#endif

#include "pch.h"

#ifdef _cplusplus

extern "C" {
    
#endif

typedef struct MainProperties
{
    float fStrength;

    float fDexterity;

    float fIntelligence;

    int iHeroLevel;
}*LPMAINPROPERTIES;

typedef struct AbilityPoint{
    int iLeft;

    int iAlready;
}*LPABILITYPOINT;

typedef struct NormalProperties{
    float fHp;

    float fMp;

    float fArmsDmg; //姝﹀櫒浼ゅ��

    float fTotalDmg;

    float fDmgAddition;

    float fArmor;

    float fPhysicalDmg;

    float fMagicalDmg;

    float fPhysicalCriticalAddition;    //鐗╃悊鐖嗙巼

    float fMagicalCriticalAddition;

    float fMagnification;

    float fPropertyDmg;

    float fFullDmg;

    float fAbilityDmg;

    float fStrengthPercent;

    float fDexterityPercent;

    float fIntelligencePercent;
    
    float fFixedDmg;

    float fPhysicalDmgIncrement;

    float fMagicalDmgIncrement;

    float fStrengthCorrection;

    float fDexterityCorrection;

    float fIntelligenceCorrection;

    float fPenetration;

    float fShieldValue;

    float fMissile;
}*LPNORMALPROPERTIES;

class WARAPPDLL_API HeroMain{
    private:

    char p_PATH_HeroImg[MAX_PATH];

    char p_szHeroName[64];

    public:
    HeroMain();

    ~HeroMain();

    char* GetName();

    void SetName(const char* szHeroName);

    void SetHeroImgPath(const char* szImgpath);

    char* GetHeroImgPath();

    LPMAINPROPERTIES lpMainProperties;

    LPABILITYPOINT lpAbilityPoint;

    LPNORMALPROPERTIES lpNormalProperties;
};

#ifdef _cplusplus
}
#endif