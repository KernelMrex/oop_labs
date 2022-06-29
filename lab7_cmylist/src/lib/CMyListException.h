#ifndef CMYLISTEXCEPTION_H
#define CMYLISTEXCEPTION_H

#include <stdexcept>

class CMyListException : public std::runtime_error
{
public:
	static CMyListException IteratorCannotBeChanged();
	static CMyListException IteratorCannotBeDeleted();
	static CMyListException CannotGetValueFromBaseNode();

private:
	explicit CMyListException(const std::string& msg);
};

#endif // CMYLISTEXCEPTION_H
