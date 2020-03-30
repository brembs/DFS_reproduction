{-------------------------------------------------------
   Delphi unit for STATISTICA Development Environment
   Copyright (c) 1997 by StatSoft, Inc.
-------------------------------------------------------}

unit StaDev32;

interface

uses Windows;

type
   HSTAFILE = longint;
   HRES = smallint;
   PSHORT = ^smallint;
   PDOUBLE = ^double;

const
   STAMAX_NVARS = 4092;
   STAMAX_VARNAMELEN = 8;
   STAMAX_LONGVARNAMELEN = 128;
   STAMAX_CASENAMELEN = 20;
   STAMAX_SLABELLEN = 8;
   STAMAX_LLABELLEN = 40;
   STAMAX_HEADERLEN = 80;
   STAMAX_NB_SLAB = 2200;
   STAMAX_NB_LLAB = 720;
   RES_OK = 1;
   RES_ERR = 0;

function StaDevVersion: longint; stdcall;
function StaOpenFile(szFileName: LPCSTR): HSTAFILE; stdcall;
function StaCreateFile(NVars: smallint; NCases: longint; szFileName: LPCSTR): HSTAFILE; stdcall;
function StaCloseFile(hSF: HSTAFILE): HRES; stdcall;

function StaGetNVars(hSF: HSTAFILE): smallint; stdcall;
function StaGetNCases(hSF: HSTAFILE): longint; stdcall;
function StaAddVars(hSF: HSTAFILE; After, HowMany: smallint): HRES; stdcall;
function StaDeleteVars(hSF: HSTAFILE; FromVar, ToVar: smallint): HRES; stdcall;
function StaAddCases(hSF: HSTAFILE; After, HowMany: longint): HRES; stdcall;
function StaDeleteCases(hSF: HSTAFILE; FromCase, ToCase: longint): HRES; stdcall;

function StaSetFileHeader(hSF: HSTAFILE; szHeader: LPCSTR): HRES; stdcall;
function StaGetFileHeader(hSF: HSTAFILE; szHeader: LPSTR; BL: smallint): HRES; stdcall;

{Variable Name functions}
function StaSetVarName(hSF: HSTAFILE; VarNum: smallint; szName: LPCSTR): HRES; stdcall;
function StaGetVarName(hSF: HSTAFILE; VarNum: smallint; szName: LPSTR): HRES; stdcall;
function StaSetVarLongName(hSF: HSTAFILE; VarNum: smallint; szLongName: LPCSTR): HRES; stdcall;
function StaGetVarLongName(hSF: HSTAFILE; VarNum: smallint; szLongName: LPSTR; BL: smallint): HRES; stdcall;

{Variable Format functions}
function StaSetVarFormat(hSF: HSTAFILE; VarNum, Width, Decs, Categ, Display: smallint): HRES; stdcall;
function StaGetVarFormat(hSF: HSTAFILE; VarNum: smallint; Width, Decs, Categ, Display: PSHORT): HRES; stdcall;

{Missing Data functions}
function StaSetVarMD(hSF: HSTAFILE; VarNum: smallint; MDValue: double): HRES; stdcall;
function StaGetVarMD(hSF: HSTAFILE; VarNum: smallint; lpMDVal: PDOUBLE): HRES; stdcall;
function StaGetAllMD(hSF: HSTAFILE; lpMD: PDOUBLE): HRES; stdcall;

{Case Name functions}
function StaSetCaseNameLength(hSF: HSTAFILE; CNLen: smallint): HRES; stdcall;
function StaGetCaseNameLength(hSF: HSTAFILE): smallint; stdcall;
function StaSetCaseName(hSF: HSTAFILE; CaseNum: longint; szName: LPCSTR): HRES; stdcall;
function StaGetCaseName(hSF: HSTAFILE; CaseNum: longint; szName: LPSTR; BL: short): HRES; stdcall;

{Data functions}
function StaSetData(hSF: HSTAFILE; VarNum: smallint; CaseNum: longint; Value: double): HRES; stdcall;
function StaGetData(hSF: HSTAFILE; VarNum: smallint; CaseNum: longint; lpValue: PDOUBLE): HRES; stdcall;
function StaSetCaseData(hSF: HSTAFILE; CaseNum: longint; lpCase: PDOUBLE): HRES; stdcall;
function StaGetCaseData(hSF: HSTAFILE; CaseNum: longint; lpCase: PDOUBLE): HRES; stdcall;

{Label functions}
function StaGetLabelForValue(hSF: HSTAFILE; VarNum: smallint; Value: double; szLabel: LPSTR): HRES; stdcall;
function StaGetLongLabelForValue(hSF: HSTAFILE; VarNum: smallint; Value: double; szLLabel: LPSTR; BL: smallint): HRES; stdcall;
function StaGetValueForLabel(hSF: HSTAFILE; VarNum: smallint; szLabel: LPCSTR; lpValue: PDOUBLE): HRES; stdcall;
function StaAddLabel(hSF: HSTAFILE; VarNum: smallint; Value: double; szLabel, szLongLabel: LPCSTR): HRES; stdcall;
function StaDeleteLabelForValue(hSF: HSTAFILE; VarNum: smallint; Value: double): HRES; stdcall;
function StaDeleteLabel(hSF: HSTAFILE; VarNum: smallint; szLabel: LPCSTR): HRES; stdcall;
function StaGetNumVarLabels(hSF: HSTAFILE; VarNum: smallint; lpNumLabels: PSHORT): HRES; stdcall;
function StaGetVarLabelByIndex(hSF: HSTAFILE; VarNum, index: smallint; lpValue: PDOUBLE; szLabel, szLongLabel: LPSTR): HRES; stdcall;


implementation

const
   stadev = 'stadev32.dll';

function StaDevVersion; external stadev name 'StaDevVersion';
function StaOpenFile; external stadev name 'StaOpenFile';
function StaCreateFile; external stadev name 'StaCreateFile';
function StaCloseFile; external stadev name 'StaCloseFile';
function StaGetNVars; external stadev name 'StaGetNVars';
function StaGetNCases; external stadev name 'StaGetNCases';
function StaAddVars; external stadev name 'StaAddVars';
function StaDeleteVars; external stadev name 'StaDeleteVars';
function StaAddCases; external stadev name 'StaAddCases';
function StaDeleteCases; external stadev name 'StaDeleteCases';
function StaSetFileHeader; external stadev name 'StaSetFileHeader';
function StaGetFileHeader; external stadev name 'StaGetFileHeader';
function StaSetVarName; external stadev name 'StaSetVarName';
function StaGetVarName; external stadev name 'StaGetVarName';
function StaSetVarLongName; external stadev name 'StaSetVarLongName';
function StaGetVarLongName; external stadev name 'StaGetVarLongName';
function StaSetVarFormat; external stadev name 'StaSetVarFormat';
function StaGetVarFormat; external stadev name 'StaGetVarFormat';
function StaSetVarMD; external stadev name 'StaSetVarMD';
function StaGetVarMD; external stadev name 'StaGetVarMD';
function StaGetAllMD; external stadev name 'StaGetAllMD';
function StaSetCaseNameLength; external stadev name 'StaSetCaseNameLength';
function StaGetCaseNameLength; external stadev name 'StaGetCaseNameLength';
function StaSetCaseName; external stadev name 'StaSetCaseName';
function StaGetCaseName; external stadev name 'StaGetCaseName';
function StaSetData; external stadev name 'StaSetData';
function StaGetData; external stadev name 'StaGetData';
function StaSetCaseData; external stadev name 'StaSetCaseData';
function StaGetCaseData; external stadev name 'StaGetCaseData';
function StaGetLabelForValue; external stadev name 'StaGetLabelForValue';
function StaGetLongLabelForValue; external stadev name 'StaGetLongLabelForValue';
function StaGetValueForLabel; external stadev name 'StaGetValueForLabel';
function StaAddLabel; external stadev name 'StaAddLabel';
function StaDeleteLabelForValue; external stadev name 'StaDeleteLabelForValue';
function StaDeleteLabel; external stadev name 'StaDeleteLabel';
function StaGetNumVarLabels; external stadev name 'StaGetNumVarLabels';
function StaGetVarLabelByIndex; external stadev name 'StaGetVarLabelByIndex';
end.
