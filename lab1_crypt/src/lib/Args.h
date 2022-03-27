#ifndef ARGS_H
#define ARGS_H

#include <optional>
#include "Action.h"

class Args final
{
public:
	static std::optional<Args> ParseFromCLI(int argc, char** argv)
	{
		if (argc != 5)
		{
			return std::nullopt;
		}

		auto action = ParseActionEnum(argv[1]);
		if (!action.has_value())
		{
			return std::nullopt;
		}

		auto key = ParseUnsignedChar(argv[4]);
		if (!key.has_value())
		{
			return std::nullopt;
		}

		return { (Args){
			action.value(),
			std::string(argv[2]),
			std::string(argv[3]),
			key.value()
		} };
	}

	[[nodiscard]] Action GetAction() const
	{
		return m_action;
	}

	[[nodiscard]]
	const std::string& GetInputFilePath() const
	{
		return m_inputFilePath;
	}

	[[nodiscard]]
	const std::string& GetOutputFilePath() const
	{
		return m_outputFilePath;
	}

	[[nodiscard]]
	unsigned char GetKey() const
	{
		return m_key;
	}

private:
	Args(Action action, std::string&& inputFilePath, std::string&& outputFilePath, unsigned char key)
		: m_action(action)
		, m_inputFilePath(inputFilePath)
		, m_outputFilePath(outputFilePath)
		, m_key(key){};

	Action m_action;
	std::string m_inputFilePath;
	std::string m_outputFilePath;
	unsigned char m_key;

	[[nodiscard]]
	static std::optional<Action> ParseActionEnum(const char* arg)
	{
		auto actionString = std::string(arg);
		Action action;
		if (actionString == "encrypt")
		{
			action = Action::ENCRYPT;
		}
		else if (actionString == "decrypt")
		{
			action = Action::DECRYPT;
		}
		else
		{
			return std::nullopt;
		}
		return action;
	}

	[[nodiscard]]
	static std::optional<unsigned char> ParseUnsignedChar(const char* arg)
	{
		unsigned char key;
		try
		{
			auto valueInt = std::stoi(arg);
			if (valueInt < 0 || valueInt > 255)
			{
				return std::nullopt;
			}

			key = static_cast<unsigned char>(valueInt);
		}
		catch (std::exception& exception)
		{
			return std::nullopt;
		}

		return key;
	}
};

#endif // ARGS_H
