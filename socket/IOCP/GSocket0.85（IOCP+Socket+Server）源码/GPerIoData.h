/********************************************************************************
*																				*
*					GSocket：完成端口通讯模块（IOCP Socket）					*
*								——GPerIoData									*
*																				*
*				Copyright © 2009  代码客（卢益贵）  版权所有					*
*						未经许可，不得用于任何项目开发							*
*  QQ:48092788  E-Mail:gcode@qq.com  源码博客：http://blog.csdn.net/guestcode	*
*																				*
*					GSN:34674B4D-1F63-11D3-B64C-11C04F79498E					*
********************************************************************************/

#pragma once

#include "GSocket.h"

/*********************************************************************************
                   类型定义
*********************************************************************************/
typedef enum _GIO_OPER_TYPE
{
GIO_READ_COMPLETED,
GIO_ZERO_READ_COMPLETED,
GIO_WRITE_COMPLETED,
GIO_CONNECTED,
GIO_CONNECTED_ERROR,
GIO_CLOSE,
GIO_IDLE_OVERTIME,
GIO_CONNECTION_OVERFLOW,
}GIO_OPER_TYPE;

typedef struct _GIO_DATA_INFO
{
OVERLAPPED			Overlapped;
#if(!_USE_SINGLY_LINKED_LIST_IN_IODATA_POOL)
_GIO_DATA_INFO		*pNext;
#endif
WSABUF				WSABuf;
GIO_OPER_TYPE		OperType;
void				*pOwner;
}GIO_DATA_INFO, *PGIO_DATA_INFO;

typedef struct _GIO_DATA
{
OVERLAPPED			Overlapped;
#if(!_USE_SINGLY_LINKED_LIST_IN_IODATA_POOL)
_GIO_DATA			*pNext;
#endif
WSABUF				WSABuf;
GIO_OPER_TYPE		OperType;
void				*pOwner;
char				cData[1];
}GIO_DATA, *PGIO_DATA;

PGIO_DATA GIoDat_Alloc(void);
void GIoDat_Free(PGIO_DATA pIoData);

extern DWORD dwGBufSize;
extern DWORD dwGBufOffset;
extern BOOL bGIoDataIsActive;

void GIoDat_Init(PGIO_DATA pIoData);
DWORD GIoDat_GetPackHeadSize(void);
void GIoDat_SetPackHeadSize(DWORD dwSize);
DWORD GIoDat_GetPackTailSize(void);
void GIoDat_SetPackTailSize(DWORD dwSize);

void GIoDat_Create(void);
void GIoDat_Destroy(void);

#define GIoDat_ResetIoDataOnAlloc(pIoData) {PGIO_DATA(pIoData)->Overlapped.Internal = 0; \
									 PGIO_DATA(pIoData)->Overlapped.InternalHigh = 0; \
									 /*PGIO_DATA(pIoData)->Overlapped.hEvent = 0; \
									 PGIO_DATA(pIoData)->Overlapped.Offset = 0; \
									 PGIO_DATA(pIoData)->Overlapped.OffsetHigh = 0;*/}
#define GIoDat_ResetIoDataOnRead(pIoData) (pIoData->Overlapped.InternalHigh = 0)
#define GIoDat_ResetIoDataOnWrite(pIoData) (pIoData->Overlapped.InternalHigh = 0)

  