#ifndef  _OBJECT_H_
#define _OBJECT_H_

#include <string>

class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual std::string Tostring();				// ���� ����׿�
	unsigned int		GetHash()		 const; // ������Ʈ ���� ID -> �ּ�
	bool operator == (const Object& Val) const; // ������Ʈ ��
	bool operator != (const Object& Val) const; // ����
};
#endif // ! _OBJECT_H_
