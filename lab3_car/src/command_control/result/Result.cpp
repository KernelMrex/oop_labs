#include "Result.h"

Result::Result(bool isSuccessful)
{
	this->isSuccessful = isSuccessful;
}

Result::Result(bool isSuccessful, std::string message)
{
	this->isSuccessful = isSuccessful;
	this->message = std::move(message);
}

bool Result::IsSuccessful() const
{
	return isSuccessful;
}

std::string Result::GetMessage() const
{
	return message;
}

Result::Result(Result&& result) noexcept
	: isSuccessful(result.isSuccessful)
	, message(std::move(result.message))
{
}
