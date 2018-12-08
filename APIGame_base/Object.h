#ifndef  _OBJECT_H_
#define _OBJECT_H_

#include <string>

class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual std::string Tostring();				// 보통 디버그용
	unsigned int		GetHash()		 const; // 오브젝트 고유 ID -> 주소
	bool operator == (const Object& Val) const; // 오브젝트 비교
	bool operator != (const Object& Val) const; // 동일
};
#endif // ! _OBJECT_H_
