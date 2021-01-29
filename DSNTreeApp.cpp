//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <fstream>

#include "DSNTreeApp.hpp"
#include <utils/utils.hpp>

void DSNTreeApp::SetUsage()
{
	us.description = "Adds parent blocks and record numbers to a native DSN file.";
	us.set_syntax("DSNTree.exe " + FILE_ARG + " [/o:" + EXTENSION_ARG + "] [/x:" + XMLDOC_ARG + "] [/t]");
	
	Unnamed_Arg file{ FILE_ARG };
	file.many = true;
	file.set_required(true);
	file.helpstring = "Filename(s) to process.";
	us.add_Argument(file);
	
	Named_Arg o{ EXTENSION_ARG };
	o.switch_char = 'o';
	o.set_type(Argument_Type::string);
	o.set_default_value(extension);
	o.helpstring = "Extension of the output file(s).";
	us.add_Argument(o);

	Named_Arg x{ XMLDOC_ARG };
	x.switch_char = 'x';
	x.set_type(Argument_Type::string);
	x.set_default_value(xmldoc);
	x.helpstring = "XML document describing the DSN structure.";
	us.add_Argument(x);

	Named_Arg t{ TRANSPOSE_ARG };
	t.switch_char = 't';
	t.set_type(Argument_Type::simple);
	t.helpstring = "Transpose wage types in columns.";
	
	us.usage = "This utility builds a file that extends the given source file(s) for better\n"
				"readability / processing.\n"
				"The XML document describes the dependencies between blocks that can be present\n"
				"in a DSN file. See DSNTree.xml that is provided with this utility and used by\n"
				"default.\n"
				"All levels of parent blocks are inserted before each block present in the input\n"
				"file. An ID is also provided for each set of common wage types, based on a\n"
				"decreasing wage type number within the same block.\n"
				"If the option transpose is used, the values of the wage types of each ID are\n"
				"printed on an unique row, using a comma ',' as delimiter.\n";
}

std::string DSNTreeApp::CheckArguments()
{
	auto ext = us.get_Argument(EXTENSION_ARG);
	if (!ext->value.empty() && !ext->value.front().empty())
	{
		extension = ext->value.front();
		if (extension[0] != '.')
			extension.insert(0, ".");
	}

	auto xml = us.get_Argument(XMLDOC_ARG);
	if (!xml->value.empty() && !xml->value.front().empty())
		xmldoc = xml->value.front();
	// TODO : validate existence of xml document

	auto trans = us.get_Argument(TRANSPOSE_ARG);
	if (!trans->value.empty() && trans->value.front() == "true")
		transpose = true;

	return "";				// all is okay
}

void DSNTreeApp::MainProcess(const std::filesystem::path& file)
{
	// initialize input file
	auto fsize = std::filesystem::file_size(file);
	auto EOL_type = file_EOL(file);
	auto EOL_len = EOL_length(EOL_type);
	char EOL_delim = '\n';
	if (EOL_type == EOL::Mac)
		EOL_delim = '\r';
	std::ifstream infile(file, std::ios::binary);
	std::uintmax_t lineCnt{ 0 };
	
	// initialize output file
	auto outpath = getOutPath(file);
	if (std::filesystem::exists(outpath))
		std::filesystem::remove(outpath);
	std::ofstream outfile(outpath, std::ios_base::out | std::ios::binary);
	std::uintmax_t outCnt{ 0 };
	
	// TODO process file

	infile.close();
	outfile.close();
}
