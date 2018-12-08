#include "Object.h"

Object::Object()
{

}
Object::~Object()
{

}

std::string Object::Tostring()
{
	return typeid(*this).name();
}
unsigned int Object::GetHash() const
{
	return reinterpret_cast<unsigned int>(this);
}
bool Object::operator == (const Object& Val) const
{
	return GetHash() == Val.GetHash();
}
bool Object::operator != (const Object& Val) const
{
	return GetHash() != Val.GetHash();
}