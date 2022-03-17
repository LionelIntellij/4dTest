#include "JsonParser.h"


JsonParser::JsonParser(const std::string&  jsonStr):
	m_positionJson(0),
	m_jsonStr(jsonStr),
	m_jsonSize(jsonStr.size())
{
}

bool JsonParser::parse()
{
	
	m_positionJson = 0;
	while (m_positionJson < m_jsonSize && m_error.empty())
	{
		switch (getTokenType())
		{
			case CURLY_OPEN:
			{
				break;
			}

			case ARRAY_OPEN:
			{
				break;
			}

			case ARRAY_CLOSED:
			{
				break;
			}

			case QUOTE:
			{
				break;
			}

			default:
			{
				m_error = " an Error occurend on the character : " +std::to_string(m_positionJson);
			}
		}
		m_positionJson++;
	}
	return true;
}


std::string JsonParser::getError()
{
	return m_error;
}



JsonParser::TokenType JsonParser::getTokenType()
{
	char jsonCharacter = m_jsonStr[m_positionJson];
	if (jsonCharacter == '"')
		return QUOTE;
	else
		return UNKNOW;
}