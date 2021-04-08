#include <string>
class Result
{
public:
	explicit Result(bool isSuccessful);

	Result(Result&& result) noexcept;

	Result(bool isSuccessful, std::string message);

	[[nodiscard]] bool IsSuccessful() const;

	[[nodiscard]] std::string GetMessage() const;

private:
	bool isSuccessful;
	std::string message;
};
