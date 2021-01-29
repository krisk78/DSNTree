#pragma once

#include <ConsoleAppFW/consoleapp.hpp>
#include <utils/utils.hpp>

class DSNTreeApp : public ConsoleApp
{
public:
	DSNTreeApp(bool window_mode) : ConsoleApp(window_mode) {};

	// final parameters storage
	std::string extension{ ".tree.txt" };
	std::string xmldoc{ "DSNTree.xml" };
	bool transpose{ false };

	// argument names of the application
	const std::string FILE_ARG{ "file" };
	const std::string EXTENSION_ARG{ "extension" };
	const std::string XMLDOC_ARG{ "xmldocument" };
	const std::string TRANSPOSE_ARG{ "transpose" };

protected:
	virtual void SetUsage() override;											// Defines expected arguments and help.
	virtual std::string CheckArguments() override;								// Performs more accurate checks and initializations if necessary
	virtual void MainProcess(const std::filesystem::path& file) override;		// Launched by ByFile for each file matching argument 'file' values

};
