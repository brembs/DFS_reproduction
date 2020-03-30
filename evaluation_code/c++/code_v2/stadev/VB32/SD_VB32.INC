Rem     VB Header File for STATISTICA Development Environment
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

Declare Function StaDevVersion Lib "stadev32.dll" () As Long
Declare Function StaOpenFile Lib "stadev32.dll" (ByVal szFileName As String) As Long
Declare Function StaCreateFile Lib "stadev32.dll" (ByVal NVars As Integer, ByVal NCases As Long, ByVal szFileName As String) As Long
Declare Function StaCloseFile Lib "stadev32.dll" (ByVal hSF As Long) As Integer
Declare Function StaGetNVars Lib "stadev32.dll" (ByVal hSF As Long) As Integer
Declare Function StaGetNCases Lib "stadev32.dll" (ByVal hSF As Long) As Long
Declare Function StaAddVars Lib "stadev32.dll" (ByVal hSF As Long, ByVal After As Integer, ByVal HowMany As Integer) As Integer
Declare Function StaDeleteVars Lib "stadev32.dll" (ByVal hSF As Long, ByVal FromVar As Integer, ByVal ToVar As Integer) As Integer
Declare Function StaAddCases Lib "stadev32.dll" (ByVal hSF As Long, ByVal After As Long, ByVal HowMany As Long) As Integer
Declare Function StaDeleteCases Lib "stadev32.dll" (ByVal hSF As Long, ByVal FromCase As Long, ByVal ToCase As Long) As Integer
Declare Function StaSetFileHeader Lib "stadev32.dll" (ByVal hSF As Long, ByVal szHeader As String) As Integer
Declare Function StaGetFileHeader Lib "stadev32.dll" (ByVal hSF As Long, ByRef szHeader As Byte, ByVal BL As Integer) As Integer
Declare Function StaSetVarName Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szName As String) As Integer
Declare Function StaGetVarName Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef szName As Byte) As Integer
Declare Function StaSetVarLongName Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLongName As String) As Integer
Declare Function StaGetVarLongName Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef szLongName As Byte, ByVal BL As Integer) As Integer
Declare Function StaSetVarFormat Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal width As Integer, ByVal dec As Integer, ByVal categ As Integer, ByVal display As Integer) As Integer
Declare Function StaGetVarFormat Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef lpWidth As Integer, ByRef lpDec As Integer, ByRef lpCateg As Integer, ByRef lpDisplay As Integer) As Integer
Declare Function StaSetVarMD Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal MDValue As Double) As Integer
Declare Function StaGetVarMD Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef lpMDVal As Double) As Integer
Declare Function StaSetCaseNameLength Lib "stadev32.dll" (ByVal hSF As Long, ByVal CNLen As Integer) As Integer
Declare Function StaGetCaseNameLength Lib "stadev32.dll" (ByVal hSF As Long) As Integer
Declare Function StaSetCaseName Lib "stadev32.dll" (ByVal hSF As Long, ByVal CaseNo As Long, ByVal szName As String) As Integer
Declare Function StaGetCaseName Lib "stadev32.dll" (ByVal hSF As Long, ByVal CaseNo As Long, ByVal szName As String, ByVal BL As Integer) As Integer
Declare Function StaSetData Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal CaseNo As Long, ByVal Value As Double) As Integer
Declare Function StaGetData Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal CaseNo As Long, ByRef Value As Double) As Integer
Declare Function StaGetLabelForValue Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByRef szLabel As Byte) As Integer
Declare Function StaGetLongLabelForValue Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByRef szLLabel As Byte, ByVal BL As Integer) As Integer
Declare Function StaGetValueForLabel Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLabel As String, ByRef lpValue As Double) As Integer
Declare Function StaAddLabel Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double, ByVal szLabel As String, ByVal szLongLabel As String) As Integer
Declare Function StaDeleteLabelForValue Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Value As Double) As Integer
Declare Function StaDeleteLabel Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal szLabel As String) As Integer
Declare Function StaGetNumVarLabels Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByRef NumLabels As Integer) As Integer
Declare Function StaGetVarLabelByIndex Lib "stadev32.dll" (ByVal hSF As Long, ByVal Var As Integer, ByVal Index As Integer, ByRef Value As Double, ByRef szLabel As Byte, ByRef szLongLabel As Byte) As Integer
