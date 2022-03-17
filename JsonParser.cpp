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
				if (!parseNode())
					m_error = " could not parse json node at the position : " + std::to_string(m_positionJson);
				break;
			}

			case ARRAY_OPEN:
			{
				if (!parseArray())
					m_error = " could not parse json array at the position : " + std::to_string(m_positionJson);
				break;
			}

			case BOOL_TYPE:
			{
				if (!parseBoolean())
					m_error = " could not parse json bool at the position : " + std::to_string(m_positionJson);
				break;
			}

			case QUOTE:
			{
				if (!parseString())
					m_error = " could not parse json bool at the position : " + std::to_string(m_positionJson);
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

bool JsonParser::parseBoolean()
{
	return true;
}

bool JsonParser::parseArray()
{
	return true;
}

bool JsonParser::parseNode()
{
	return true;
}

bool JsonParser::parseString()
{
	JsonParser::TokenType type = UNKNOW;
	size_t prevPos = m_positionJson;
	m_positionJson++;
	std::string value;
	while (getTokenType() != QUOTE 
		&& type == UNKNOW
		&& m_positionJson< m_jsonSize)
	{
		value += m_jsonStr[m_positionJson];
		m_positionJson++;
	}
	if (getTokenType() != QUOTE)
	{
		//TODO  get Key
		m_error = "";
		m_positionJson = prevPos;
	}
	else
	{
		//TODO  get Key
		///m_json[].strValue = 
	}
	return true;
}


std::string JsonParser::getError()
{
	return m_error;
}



JsonParser::TokenType JsonParser::getTokenType()
{
	char jsonCharacter ='\n';

	while ((jsonCharacter == ' ' || jsonCharacter == '\n') && m_positionJson< m_jsonSize)
	{
		jsonCharacter = m_jsonStr[m_positionJson];
		m_positionJson++;
	}

	if (jsonCharacter == '"')
	{
		return QUOTE;
	}
	else if (jsonCharacter == '[')
	{
		return ARRAY_OPEN;
	}
	else if (jsonCharacter == ']')
	{
		return ARRAY_CLOSE;
	}
	else if (jsonCharacter == ':')
	{
		return SEMICOLON;
	}
	else if (jsonCharacter == ',')
	{
		return COMMA;
	}
	else if (jsonCharacter == 'f')
	{
		return BOOL_TYPE;
	}
	else if (jsonCharacter == 't')
	{
		return BOOL_TYPE;
	}
	else
		return UNKNOW;
}