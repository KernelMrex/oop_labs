#include "CMyListException.h"

CMyListException::CMyListException(const std::string& msg)
	: runtime_error(msg)
{
}

CMyListException CMyListException::IteratorCannotBeChanged()
{
	return CMyListException("Iterator can not be changed");
}

CMyListException CMyListException::IteratorCannotBeDeleted()
{
	return CMyListException("Iterator can not be deleted");
}

CMyListException CMyListException::CannotGetValueFromBaseNode()
{
	return CMyListException("Can not get value from base node");
}
