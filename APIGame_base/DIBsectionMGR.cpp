#include "DIBsectionMGR.h"

DIBsectionMGR* DIBsectionMGR::m_instance;

DIBsectionMGR::DIBsectionMGR()
{

}
DIBsectionMGR::~DIBsectionMGR()
{

}
HBITMAP DIBsectionMGR::MakeDIBSection(char* Path)
{
	hFile = CreateFile((LPCWSTR)Path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	// 파일 헤더와 정보 구조체(색상 테이블 포함) 을 읽어들인다.
	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	Filesize = fh.bfOffBits - sizeof(BITMAPFILEHEADER);
	ih = new BITMAPINFO; // (BITMAPINFO*)malloc(Filesize);
	ReadFile(hFile, ih, Filesize, &dwRead, NULL);

	// DIB 섹션 생성 , 버퍼 메모리 할당
	hbit = CreateDIBSection(NULL, ih, DIB_RGB_COLORS, &pRaster, NULL, 0);

	// 래스터 데이터 읽기
	ReadFile(hFile, pRaster, fh.bfSize - fh.bfOffBits, &dwRead, NULL);
	delete(ih);
	CloseHandle(hFile);

	return hbit;
}
