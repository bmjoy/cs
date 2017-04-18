// FileOperateClass.cpp: implementation of the CFileOperateClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileOperateClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperateClass::CFileOperateClass()
{
	int i = 0;
}

CFileOperateClass::~CFileOperateClass()
{

}


VOID  CFileOperateClass::GetFilePath( IN  OUT   PCHAR  lpFileName )
{
	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );
	
	string strTempMemoryPath = szFilePath;

	///////////////////////////���ͺ�λ�������number��ǰ׺ -- n
	int nPos = strTempMemoryPath.find_last_of( "\\" );

	strTempMemoryPath = strTempMemoryPath.substr( 0, (nPos + 1) );

	strTempMemoryPath.append( lpFileName );

	memset( lpFileName, 0, MAX_PATH );
	
	strcpy( lpFileName, strTempMemoryPath.c_str() );

	_strlwr( lpFileName );
}


VOID  CFileOperateClass::GetFilePath( IN  OUT   string  &strFileName )
{
 	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );

	string strFilePath = szFilePath;
	
	///////////////////////////���ͺ�λ�������number��ǰ׺ -- n
	int nPos = strFilePath.find_last_of( "\\" );
	
	strFilePath = strFilePath.substr( 0, (nPos + 1) );
	
	strFilePath.append( strFileName );

	strFileName = strFilePath;
}


BOOL  CFileOperateClass::ReadFile( IN        PCHAR             lpFileFullPath,
								   IN  OUT   PDATA_STRUCTURE   &pDataStructure )
{	
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        PCHAR             lpFileFullPath,
									IN        PDATA_STRUCTURE   pDateStructure )
{
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        unsigned char       *pchBuffer,
								    IN 	      const UINT           nDataLength,
								    IN        string               strFileFullPath )
{
	//���ļ�
	FILE *pFileW = NULL;
	
	pFileW = fopen( strFileFullPath.c_str(), "w+" );

	if ( NULL == pFileW )
	{
		return FALSE;
	}

	//д���ļ�
	fseek(pFileW, 0, SEEK_CUR); 

	fwrite( pchBuffer, sizeof(char), nDataLength, pFileW);

	char szTemp[1024] = {0};
	
	for( int i = 0; i < 1433; i++ )
	{
		fwrite( szTemp, sizeof(char), nDataLength, pFileW );
	}

	//�ر��ļ�
	if ( fclose(pFileW) )
	{
		return FALSE;
	}
	
	return TRUE;
}

int CFileOperateClass::ReadFile( IN OUT    unsigned char       *pchBuffer,
								 IN 	   const UINT           nDataLength,
								 IN        string               strFileFullPath )
{
//	ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_FileOpeateProcessMutex, -1 );
	
	FILE *pFile = NULL;

	pFile = fopen( strFileFullPath.c_str(), "rb" );

	if( NULL == pFile)
	{
		return -1;
	}

	fseek( pFile, 0, SEEK_SET );				//////////Moves the file pointer to a specified location
	
	int numread = fread( (PCHAR)pchBuffer,
						 nDataLength,
						 1,
						 pFile );

	long lPos = ftell(pFile);					//////////Gets the current position of a file pointer.

	if ( fclose(pFile) )
	{
		return -1;
	}
	
	return 0;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
int CFileOperateClass::ParseConnectDbConfigurationFile(
									IN    OUT   string    &strConnection,
									IN          string     strIp,
									IN    OUT   string    &strUseID,
									IN    OUT   string	  &strPassWord,
									IN          string     strFileFullPathName )
{	
	PCONNECT_DB_CONFIGURATION_FILE pBuffer = new CONNECT_DB_CONFIGURATION_FILE;
	
	int nDataLength = sizeof( CONNECT_DB_CONFIGURATION_FILE );
	
	memset( (PCHAR)pBuffer, 0, nDataLength );
	
	int nStatus = CFileOperateClass::ReadFile( (unsigned char*)pBuffer,
											   nDataLength,
											   strFileFullPathName );
	
	if ( 0 == nStatus )
	{		
		strConnection  =  "Provider=";
		strConnection +=  pBuffer->Provider;
		strConnection +=  ";";
		strConnection +=  "Persist Security Info=";
		strConnection +=  pBuffer->PerSInfo;
		strConnection +=  ";";
		strConnection +=  "NETWORK=DBMSSOCN;";
		strConnection +=  "User ID=";
		strConnection +=  pBuffer->UserID;
		strConnection +=  ";";
		strConnection +=  "Initial Catalog=";
		strConnection +=  pBuffer->InitialCatalog;
		strConnection +=  ";";
		strConnection +=  "Data Source=";
		strConnection +=  pBuffer->DataSource;
		strConnection +=  ",";
		strConnection +=  pBuffer->port;
		
		if( strlen(pBuffer->Other) > 0 )
		{
			strConnection +=  ";";
			strConnection +=  pBuffer->Other;
			strConnection +=  ";";
		}
		strUseID     = pBuffer->UserID;
		strPassWord  = pBuffer->PassWord;
		
		strIp.assign(pBuffer->DataSource);
	}
	
	strConnection += "\n" + strUseID + "\n" + strPassWord + "\n" + strIp;
	
	::MessageBox( NULL, strConnection.c_str(), "", MB_OK );

	delete pBuffer;
	
	return nStatus;
}


//����Ҫȷ����Ļ��ȡ������,��LPRECT�ṹ������.���Խ�ȡһ������,��������Ļ.���´����ѡ������Ļ���򿽱���λͼ��. 
HBITMAP CFileOperateClass::CopyScreenToBitmap(LPRECT lpRect)
//lpRect ����ѡ������
{
	HDC hScrDC, hMemDC;
	// ��Ļ���ڴ��豸������

	HBITMAP hBitmap, hOldBitmap;
	// λͼ���

	int nX, nY, nX2, nY2;
	// ѡ����������

	int nWidth, nHeight;
	// λͼ���Ⱥ͸߶�

	int xScrn, yScrn;
	// ��Ļ�ֱ���

	// ȷ��ѡ������Ϊ�վ���
	if ( IsRectEmpty(lpRect) )
	{
		return NULL;
	}
	
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC( "DISPLAY", NULL, NULL, NULL );

	//Ϊ��Ļ�豸�������������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC( hScrDC );

	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);

	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
	{
		nX = 0;
	}
	
	if (nY < 0)
	{
		nY = 0;
	}
	
	if (nX2 > xScrn)
	{
		nX2 = xScrn;
	}

	if (nY2 > yScrn)
	{
		nY2 = yScrn;
	}
	
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// ����һ������Ļ�豸���������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);

	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// ����Ļ�豸�������������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);

	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	//���
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	// ����λͼ���
	return hBitmap;
}


//����Ҳ���԰���Ļ������λͼ��ʽ�浽�����ļ���.
int CFileOperateClass::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���
{
	//lpFileName Ϊλͼ�ļ���
	HDC hDC;
	//�豸������
	int iBits;
	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
	WORD wBitCount;
	//λͼ��ÿ��������ռ�ֽ���
	//�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ���
	DWORD dwPaletteSize=0, dwBmBitsSize, dwDIBSize, dwWritten;

	BITMAP Bitmap;
	//λͼ���Խṹ
	BITMAPFILEHEADER bmfHdr;
	//λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER bi;
	//λͼ��Ϣͷ�ṹ
	LPBITMAPINFOHEADER lpbi;
	//ָ��λͼ��Ϣͷ�ṹ
	HANDLE fh, hDib, hPal,hOldPal=NULL;
	//�����ļ��������ڴ�������ɫ����

	//����λͼ�ļ�ÿ��������ռ�ֽ���
	hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) *
	GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	
	if (iBits <= 1)
	wBitCount = 1;
	else if (iBits <= 4)
	wBitCount = 4;
	else if (iBits <= 8)
	wBitCount = 8;
	else if (iBits <= 24)
	wBitCount = 24;
	
	//�����ɫ���С
	if (wBitCount <= 8)
	{
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);
	}

	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;

	//Ϊλͼ���ݷ����ڴ�
	hDib = GlobalAlloc( GHND,
						dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER) );

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);

	*lpbi = bi;

	// ������ɫ��
	hPal = GetStockObject(DEFAULT_PALETTE);

	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal = (HANDLE)SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits( hDC,
			   hBitmap,
			   0,
			   (UINT)Bitmap.bmHeight,
			   (LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize,
			   (LPBITMAPINFO)lpbi,
			   DIB_RGB_COLORS );

	//�ָ���ɫ��
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	//����λͼ�ļ�
	fh = CreateFile( lpFileName,
					 GENERIC_WRITE,
					 0,
					 NULL,
					 CREATE_ALWAYS,
					 FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,
					 NULL );

	if (fh == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	// ����λͼ�ļ�ͷ
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	// д��λͼ�ļ�ͷ
	::WriteFile( fh,
			     (LPSTR)&bmfHdr,
			     sizeof(BITMAPFILEHEADER),
			     &dwWritten,
			     NULL );

	// д��λͼ�ļ���������
	::WriteFile( fh,
			     (LPSTR)lpbi,
			     dwDIBSize,
			     &dwWritten,
			     NULL );
	
	//���
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return 0;
}