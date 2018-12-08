#ifndef  _DIBSECTIONMGR_H_
#define  _DIBSECTIONMGR_H_

#include <Windows.h>

#define DIB_INSTANCE DIBsectionMGR::Getinstance()

class DIBsectionMGR 
{
private:
	static DIBsectionMGR* m_instance;
public:
	static DIBsectionMGR* Getinstance()
	{
		if (m_instance == NULL) m_instance = new DIBsectionMGR;
		return m_instance;
	}

public:
	DIBsectionMGR();
	~DIBsectionMGR();
public:
	HBITMAP MakeDIBSection(char* Path);

public:
	BITMAPFILEHEADER fh;
	BITMAPINFO		*ih;
	HBITMAP			 hbit;
	HANDLE			 hFile;
	PVOID			 pRaster;
	DWORD			 Filesize, dwRead;

};

#endif // ! _DIBSECTIONMGR_H_

