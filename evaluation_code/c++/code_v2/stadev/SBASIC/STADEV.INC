{*****************************************************************************
*   STATISTICA BASIC Header File for STATISTICA Development Environment      *
*   Copyright (c) 1997 by StatSoft, Inc.                                     *
*****************************************************************************}

const     STAMAX_NVARS            = 4092;
const     STAMAX_VARNAMELEN       = 8;
const     STAMAX_LONGVARNAMELEN   = 128;
const     STAMAX_CASENAMELEN      = 20;
const     STAMAX_SLABELLEN        = 8;
const     STAMAX_LLABELLEN        = 40;
const     STAMAX_HEADERLEN        = 80;
const     STAMAX_NB_SLAB          = 2200;
const     STAMAX_NB_LLAB          = 720;

const     RES_OK   = 1;
const     RES_ERR  = 0;


DECLARE FUNCTION StaDevVersion	         LIB "stadev.dll" AS long;
DECLARE FUNCTION StaOpenFile             LIB "stadev.dll" (string) AS long;
DECLARE FUNCTION StaCreateFile           LIB "stadev.dll" (integer, long, string) AS long;
DECLARE FUNCTION StaCloseFile            LIB "stadev.dll" (long) AS integer;
DECLARE FUNCTION StaGetNVars             LIB "stadev.dll" (long) AS integer;
DECLARE FUNCTION StaGetNCases            LIB "stadev.dll" (long) AS long;
DECLARE FUNCTION StaAddVars              LIB "stadev.dll" (long, integer, integer) AS integer;
DECLARE FUNCTION StaDeleteVars           LIB "stadev.dll" (long, integer, integer) AS integer;
DECLARE FUNCTION StaAddCases             LIB "stadev.dll" (long, long, long) AS integer;
DECLARE FUNCTION StaDeleteCases          LIB "stadev.dll" (long, long, long) AS integer;
DECLARE FUNCTION StaSetFileHeader        LIB "stadev.dll" (long, string) AS integer;
DECLARE FUNCTION StaGetFileHeader        LIB "stadev.dll" (long, pointer to string, integer) AS integer;
DECLARE FUNCTION StaSetVarName           LIB "stadev.dll" (long, integer, string) AS integer;
DECLARE FUNCTION StaGetVarName           LIB "stadev.dll" (long, integer, pointer to string) AS integer;
DECLARE FUNCTION StaSetVarLongName       LIB "stadev.dll" (long, integer, string) AS integer;
DECLARE FUNCTION StaGetVarLongName       LIB "stadev.dll" (long, integer, pointer to string, integer) AS integer;
DECLARE FUNCTION StaSetVarFormat         LIB "stadev.dll" (long, integer, integer, integer, integer, integer) AS integer;
DECLARE FUNCTION StaGetVarFormat         LIB "stadev.dll" (long, integer, pointer to integer, pointer to integer, pointer to integer, pointer to integer) AS integer;
DECLARE FUNCTION StaSetVarMD             LIB "stadev.dll" (long, integer, double) AS integer;
DECLARE FUNCTION StaGetVarMD             LIB "stadev.dll" (long, integer, pointer to double) AS integer;
DECLARE FUNCTION StaGetAllMD             LIB "stadev.dll" (long, pointer to double) AS integer;
DECLARE FUNCTION StaSetCaseNameLength    LIB "stadev.dll" (long, integer) AS integer;
DECLARE FUNCTION StaGetCaseNameLength    LIB "stadev.dll" (long) AS integer;
DECLARE FUNCTION StaSetCaseName          LIB "stadev.dll" (long, long, string) AS integer;
DECLARE FUNCTION StaGetCaseName          LIB "stadev.dll" (long, long, pointer to string, integer) AS integer;
DECLARE FUNCTION StaSetData              LIB "stadev.dll" (long, integer, long, double) AS integer;
DECLARE FUNCTION StaGetData              LIB "stadev.dll" (long, integer, long, pointer to double) AS integer;
DECLARE FUNCTION StaSetCaseData          LIB "stadev.dll" (long, long, pointer to double) AS integer;
DECLARE FUNCTION StaGetCaseData          LIB "stadev.dll" (long, long, pointer to double) AS integer;
DECLARE FUNCTION StaGetLabelForValue     LIB "stadev.dll" (long, integer, double, pointer to string) AS integer;
DECLARE FUNCTION StaGetLongLabelForValue LIB "stadev.dll" (long, integer, double, pointer to string, integer) AS integer;
DECLARE FUNCTION StaGetValueForLabel     LIB "stadev.dll" (long, integer, string, pointer to double) AS integer;
DECLARE FUNCTION StaAddLabel             LIB "stadev.dll" (long, integer, double, string, string) AS integer;
DECLARE FUNCTION StaDeleteLabelForValue  LIB "stadev.dll" (long, integer, double) AS integer;
DECLARE FUNCTION StaDeleteLabel          LIB "stadev.dll" (long, integer, string) AS integer;
DECLARE FUNCTION StaGetNumVarLabels      LIB "stadev.dll" (long, integer, pointer to integer) AS integer;
DECLARE FUNCTION StaGetVarLabelByIndex   LIB "stadev.dll" (long, integer, integer, pointer to double, pointer to string, pointer to string) AS integer;
