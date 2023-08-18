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

    #define LOGERROR_INITLOGGERDEFAULTPATHISNULL -(ERRORCODE+5)

    #define LOGERROR_SETFILEPOINRTERFAILED -(ERRORCODE+6)

enum ErrorDefinition{
    Success = 0,
    Error,
    Warn,
};

DWORD WARAPPDLL_API __stdcall ExecuteLogger(LPVOID lpBuffer);

DWORD WARAPPDLL_API __stdcall InitLogger(char* p_PATH_szRoute);

long WARAPPDLL_API __stdcall GetExternErrorCode();

void WARAPPDLL_API __stdcall SetExternErrorCode(long& lErrorCode);

HANDLE WARAPPDLL_API __stdcall GetLogHandleBegin();

HANDLE WARAPPDLL_API __stdcall GetLogHandleEnd();

#ifdef _cplusplus

}

#endif