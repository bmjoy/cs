// Request.cpp : implementation of the CRequest class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1997-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#include "HttpSvr.h"
#include "Request.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRequest, CObject)

CRequest::CRequest( void )
{
	m_nRefs = 1;
	m_bDone = FALSE;
	m_dwExecute = 0;
	m_cbBody = 0;
	m_dwAttr = 0;
	m_uStatus = 0;
	m_cbSent = 0;
	m_timeReq = CTime::GetCurrentTime();
}

CRequest::~CRequest( void )
{
}

CString CRequest::GetHeaderValue( CString strName )
{
	CString strValue;
	strName.MakeLower();
	m_mapHeaders.Lookup( strName, strValue );
	return strValue;
}

int CRequest::AddRef( void )
{
	return ++m_nRefs;
}

int CRequest::Release( void )
{
	int nRefs = --m_nRefs;
	if ( nRefs == 0 )
		delete this;
	return nRefs;
}
