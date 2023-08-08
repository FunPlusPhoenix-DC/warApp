#ifndef LOGRECORD_H_

#define LOGRECORD_H_

#endif

#include "pch.h"

#include <iostream>

#ifdef _cplusplus

extern "C"{

#endif  //begin to define

    #define ERRORCODE 200

    #define LOGERROR_CANNOTSETLOGFILE -(ERRORCODE+1)

    #define LOGERROR_CANNOTSETLOGDIR -(ERRORCODE+2)

    #define LOGERROR_FILEPOINTERISNULL -(ERRORCODE+3)

    #define LOGERROR_WRITEFILEERROR -(ERRORCODE+4)

enum ErrorDefinition{
    Success = 0,
    Error,
    Warn,
};

int WARAPPDLL_API __stdcall ExecuteLogger(std::string& strContent);

int WARAPPDLL_API __stdcall InitLogger(char* p_PATH_szRoute);

long WARAPPDLL_API __stdcall GetExternErrorCode();

void WARAPPDLL_API __stdcall SetExternErrorCode(long& lErrorCode);

#ifdef _cplusplus

}

#endif