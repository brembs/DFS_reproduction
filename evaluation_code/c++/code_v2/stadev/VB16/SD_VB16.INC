Rem     VB-16 Header File for STATISTICA Development Environment
Rem     Copyright (c) 1997 by StatSoft, Inc.

Public Const STAMAX_NVARS = 4092
Public Const STAMAX_VARNAMELEN = 8
Public Const STAMAX_LONGVARNAMELEN = 128
Public Const STAMAX_CASENAMELEN = 20
Public Const STAMAX_SLABELLEN = 8
Public Const STAMAX_LLABELLEN = 40
Public Const STAMAX_HEADERLEN = 80
Public Const STAMAX_NB_SLAB = 2200
Public Const STAMAX_NB_LLAB = 720

Public Const RES_OK = 1
Public Const RES_ERR = 0

Declare Function StaDevVersion Lib "stadev.dll" () As Long
Declare Function StaOpenFile Lib "stadev.dll" (ByVal szFileName As String) As Long
Declare Function StaCreateFile Lib "stadev.dll" (ByVal NVars As Integer, ByVal NCases As Long, ByVal szFileName As String) As Long
Declare Function StaCloseFile Lib "stadev.dll" (ByVal hSF As Long) As Integer
Declare Function StaGetNVars Lib "stadev.dll" (ByVal hSF As Long) As Integer
Declare Function StaGetNCases Lib "stadev.dll" (ByVal hSF As Long) As Long
Declare Function StaAddVars Lib "stadev.dll" (ByVal hSF As Long, ByVal After As Integer, ByVal HowMany As Integer) As Integer
Declare Function StaDeleteVars Lib "stadev.dll" (ByVal hSF As Long, ByVal FromVar As Integer, ByVal ToVar As Integer) As Integer
Declare Function StaAddCases Lib "stadev.dll" (ByVal hSF As Long, ByVal After As Long, ByVal HowMany As Long) As Integer
Declare Function StaDeleteCases Lib "stadev.dll" (ByVal hSF As Long, ByVal FromCase As Long, ByVal ToCase As Long) As Integer
Declare Function StaSetFileHeader Lib "stadev.dll" (ByVal hSF As Long, ByVal szHeader As String) As Integer
Declare Function StaGetFileHeader16 Lib "stadev.dll" Alias "StaGetFileHeader" (ByVal hSF As Long, ByVal szHeader As String, ByVal BL As Integer) As Integer
Declare Function StaSetVarName Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szName As String) As Integer
Declare Function StaGetVarName16 Lib "stadev.dll" Alias "StaGetVarName" (ByVal hSF As Long, ByVal Var As Integer, ByVal szName As String) As Integer
Declare Function StaSetVarLongName Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLongName As String) As Integer
Declare Function StaGetVarLongName16 Lib "stadev.dll" Alias "StaGetVarLongName" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLongName As String, ByVal BL As Integer) As Integer
Declare Function StaSetVarFormat Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal width As Integer, ByVal dec As Integer, ByVal categ As Integer, ByVal display As Integer) As Integer
Declare Function StaGetVarFormat Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef lpWidth As Integer, ByRef lpDec As Integer, ByRef lpCateg As Integer, ByRef lpDisplay As Integer) As Integer
Declare Function StaSetVarMD Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal MDValue As Double) As Integer
Declare Function StaGetVarMD Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef lpMDVal As Double) As Integer
Declare Function StaSetCaseNameLength Lib "stadev.dll" (ByVal hSF As Long, ByVal CNLen As Integer) As Integer
Declare Function StaGetCaseNameLength Lib "stadev.dll" (ByVal hSF As Long) As Integer
Declare Function StaSetCaseName Lib "stadev.dll" (ByVal hSF As Long, ByVal CaseNo As Long, ByVal szName As String) As Integer
Declare Function StaGetCaseName16 Lib "stadev.dll" Alias "StaGetCaseName" (ByVal hSF As Long, ByVal CaseNo As Long, ByVal szName As String, ByVal BL As Integer) As Integer
Declare Function StaSetData Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal CaseNo As Long, ByVal Value As Double) As Integer
Declare Function StaGetData Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal CaseNo As Long, ByRef Value As Double) As Integer
Declare Function StaGetLabelForValue16 Lib "stadev.dll" Alias "StaGetLabelForValue" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByVal szLabel As String) As Integer
Declare Function StaGetLongLabelForValue16 Lib "stadev.dll" Alias "StaGetLongLabelForValue" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByVal szLLabel As String, ByVal BL As Integer) As Integer
Declare Function StaGetValueForLabel Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLabel As String, ByRef lpValue As Double) As Integer
Declare Function StaAddLabel Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByVal szLabel As String, ByVal szLongLabel As String) As Integer
Declare Function StaDeleteLabelForValue Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double) As Integer
Declare Function StaDeleteLabel Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLabel As String) As Integer
Declare Function StaGetNumVarLabels Lib "stadev.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef NumLabels As Integer) As Integer
Declare Function StaGetVarLabelByIndex16 Lib "stadev.dll" Alias "StaGetVarLabelByIndex" (ByVal hSF As Long, ByVal Var As Integer, ByVal Index As Integer, ByRef Value As Double, ByVal szLabel As String, ByVal szLongLabel As String) As Integer

Function StaGetFileHeader(ByVal hSF As Long, ByRef szHeader As String, ByVal BL As Integer) As Integer
    Dim s As String
    s = String(BL, Chr(0))
    res = StaGetFileHeader16(hSF, s, BL)
    szHeader = Left(s, InStr(s, Chr(0)) - 1)
    StaGetFileHeader = res
End Function

Function StaGetVarName(ByVal hSF As Long, ByVal Var As Integer, ByRef szName As String) As Integer
    Dim s As String
    s = String(STAMAX_VARNAMELEN + 1, Chr(0))
    res = StaGetVarName16(hSF, Var, s)
    szName = Left(s, InStr(s, Chr(0)) - 1)
    StaGetVarName = res
End Function

Function StaGetVarLongName(ByVal hSF As Long, ByVal Var As Integer, ByRef szLongName As String, ByVal BL As Integer) As Integer
    Dim s As String
    s = String(BL + 1, Chr(0))
    res = StaGetVarLongName16(hSF, Var, s, BL)
    szLongName = Left(s, InStr(s, Chr(0)) - 1)
    StaGetVarLongName = res
End Function

Function StaGetCaseName(ByVal hSF As Long, ByVal CaseNo As Long, ByRef szName As String, ByVal BL As Integer) As Integer
    Dim s As String
    s = String(BL + 1, Chr(0))
    res = StaGetCaseName16(hSF, CaseNo, s, BL)
    szName = Left(s, InStr(s, Chr(0)) - 1)
    StaGetCaseName = res
End Function

Function StaGetLabelForValue(ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByRef szLabel As String) As Integer
    Dim s As String
    s = String(STAMAX_SLABELLEN + 1, Chr(0))
    res = StaGetLabelForValue16(hSF, Var, Value, s)
    szLabel = Left(s, InStr(s, Chr(0)) - 1)
    StaGetLabelForValue = res
End Function

Function StaGetLongLabelForValue(ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByRef szLLabel As String, ByVal BL As Integer) As Integer
    Dim s As String
    s = String(BL + 1, Chr(0))
    res = StaGetLongLabelForValue16(hSF, Var, Value, s, BL)
    szLLabel = Left(s, InStr(s, Chr(0)) - 1)
    StaGetLongLabelForValue = res
End Function

Function StaGetVarLabelByIndex (ByVal hSF As Long, ByVal Var As Integer, ByVal Index As Integer, ByRef Value As Double, ByRef szLabel As String, ByRef szLongLabel As String) As Integer
    Dim s As String
	Dim s1 as String
    s = String(STAMAX_SLABELLEN + 1, Chr(0))
    s1 = String(STAMAX_LLABELLEN + 1, Chr(0))
    res = StaGetVarLabelByIndex16(hSF, Var, Index, Value, s, s1)
    szLabel = Left(s, InStr(s, Chr(0)) - 1)
    szLongLabel = Left(s1, InStr(s1, Chr(0)) - 1)
    StaGetVarLabelByIndex = res
End Function
