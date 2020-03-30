// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE NSViewsDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("NSVIEWS.DLL Initializing!\n");
        
        // Extension DLL one-time initialization
        AfxInitExtensionModule(NSViewsDLL, hInstance);

        // Insert this DLL into the resource chain
        new CDynLinkLibrary(NSViewsDLL);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("NSVIEWS.DLL Terminating!\n");

		AfxTermExtensionModule(NSViewsDLL);
    }
    return 1;   // ok
}
