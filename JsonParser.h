#include <string>

class JsonParser
{

public:
	JsonParser(const std::string & jsonStr);
	bool parse();
	std::string getError();

private:
	std::string m_jsonStr;
	std::string m_error;


};