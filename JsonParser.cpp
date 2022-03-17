#include "JsonParser.h"


JsonParser::JsonParser(const std::string&  jsonStr):
	m_jsonStr(jsonStr)
{

}

bool JsonParser::parse()
{
	return true;
}


std::string JsonParser::getError()
{
	return m_error;
}