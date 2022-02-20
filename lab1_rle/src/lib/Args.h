#ifndef ARGS_H
#define ARGS_H

#include <optional>
#include <string>
#include "ActionEnum.h"

class Args final
{
public:
	static std::optional<Args> parseFromCLI(int argc, char** argv)
	{
		if (argc != 4)
		{
			return std::nullopt;
		}

		auto actionString = std::string(argv[1]);
		ActionEnum action;
		if (actionString == "pack")
		{
			action = ActionEnum::PACK;
		}
		else if (actionString == "unpack")
		{
			action = ActionEnum::UNPACK;
		}
		else
		{
			return std::nullopt;
		}

		return { (Args){
			action,
			std::string(argv[2]),
			std::string(argv[3])
		} };
	}

	[[nodiscard]]
	ActionEnum getAction() const
	{
		return m_action;
	}

	[[nodiscard]]
	const std::string& getInputFilePath() const
	{
		return m_inputFilePath;
	}

	[[nodiscard]]
	const std::string& getOutputFilePath() const
	{
		return m_outputFilePath;
	}

private:
	Args(ActionEnum action, std::string&& inputFilePath, std::string&& outputFilePath)
		: m_action(action)
		, m_inputFilePath(inputFilePath)
		, m_outputFilePath(outputFilePath){};

	ActionEnum m_action;
	std::string m_inputFilePath;
	std::string m_outputFilePath;
};

#endif // ARGS_H