/*
 * PROJECT:     sendmail
 * LICENSE:     LGPL-2.1+ (https://spdx.org/licenses/LGPL-2.1+)
 * PURPOSE:     DeskLink implementation
 * COPYRIGHT:   Copyright 2019 Katayama Hirofumi MZ (katayama.hirofumi.mz@gmail.com)
 */

#include "precomp.hpp"

WINE_DEFAULT_DEBUG_CHANNEL(sendmail);

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_DeskLinkDropHandler, CDeskLinkDropHandler)
END_OBJECT_MAP()

CComModule gModule;
LONG g_ModuleRefCnt = 0;

STDAPI DllCanUnloadNow(void)
{
    if (g_ModuleRefCnt)
        return S_FALSE;
    return gModule.DllCanUnloadNow();
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    TRACE("CLSID:%s,IID:%s\n", wine_dbgstr_guid(&rclsid), wine_dbgstr_guid(&riid));

    HRESULT hr = gModule.DllGetClassObject(rclsid, riid, ppv);

    TRACE("-- pointer to class factory: %p\n", *ppv);

    return hr;
}

STDAPI DllRegisterServer(void)
{
    HRESULT hr = gModule.DllRegisterServer(FALSE);
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    return S_OK;
}

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = gModule.DllUnregisterServer(FALSE);
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    return S_OK;
}

HRESULT
CreateShellLink(
    LPCWSTR pszLinkPath,
    LPCWSTR pszTargetPath OPTIONAL,
    LPCITEMIDLIST pidlTarget OPTIONAL,
    LPCWSTR pszArg OPTIONAL,
    LPCWSTR pszDir OPTIONAL,
    LPCWSTR pszIconPath OPTIONAL,
    INT iIconNr OPTIONAL,
    LPCWSTR pszComment OPTIONAL)
{
    CComPtr<IShellLinkW> psl;
    HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL,
                                  CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARG(IShellLinkW, &psl));
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    if (pszTargetPath)
    {
        hr = psl->SetPath(pszTargetPath);
        if (FAILED_UNEXPECTEDLY(hr))
            return hr;
    }
    else if (pidlTarget)
    {
        hr = psl->SetIDList(pidlTarget);
        if (FAILED_UNEXPECTEDLY(hr))
            return hr;
    }
    else
    {
        ERR("invalid argument\n");
        return E_INVALIDARG;
    }

    if (pszArg)
        hr = psl->SetArguments(pszArg);

    if (pszDir)
        hr = psl->SetWorkingDirectory(pszDir);

    if (pszIconPath)
        hr = psl->SetIconLocation(pszIconPath, iIconNr);

    if (pszComment)
        hr = psl->SetDescription(pszComment);

    CComPtr<IPersistFile> ppf;
    hr = psl->QueryInterface(IID_PPV_ARG(IPersistFile, &ppf));
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    hr = ppf->Save(pszLinkPath, TRUE);
    if (FAILED_UNEXPECTEDLY(hr))
        return hr;

    return hr;
}

STDAPI_(BOOL) DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID fImpLoad)
{
    TRACE("%p 0x%x %p\n", hInstance, dwReason, fImpLoad);
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        gModule.Init(ObjectMap, hInstance, NULL);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        gModule.Term();
    }
    return TRUE;
}
