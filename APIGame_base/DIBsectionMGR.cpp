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

	// ���� ����� ���� ����ü(���� ���̺� ����) �� �о���δ�.
	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	Filesize = fh.bfOffBits - sizeof(BITMAPFILEHEADER);
	ih = new BITMAPINFO; // (BITMAPINFO*)malloc(Filesize);
	ReadFile(hFile, ih, Filesize, &dwRead, NULL);

	// DIB ���� ���� , ���� �޸� �Ҵ�
	hbit = CreateDIBSection(NULL, ih, DIB_RGB_COLORS, &pRaster, NULL, 0);

	// ������ ������ �б�
	ReadFile(hFile, pRaster, fh.bfSize - fh.bfOffBits, &dwRead, NULL);
	delete(ih);
	CloseHandle(hFile);

	return hbit;
}
