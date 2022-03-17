#include "JsonParser.h"


JsonParser::JsonParser(const std::string&  jsonStr):
	m_positionJson(0),
	m_jsonStr(jsonStr),
	m_jsonSize(jsonStr.size()),
	m_rootNode(nullptr)
{
}

bool JsonParser::parse()
{
	
	m_rootNode = new Node;
	m_positionJson = 0;
	std::string keyRoot = "keyRoot";
	m_rootNode->key = keyRoot;
	while (m_positionJson < m_jsonSize && m_error.empty())
	{
		switch (getTokenType())
		{
			
			case CURLY_OPEN:
			{
				Node* node = parseNode();
				if (!node)
				{
					m_error = " Could not parse json node at the position : " + std::to_string(m_positionJson);
					return false;
				}
				m_rootNode->type = Node::Type::NODE;
				m_rootNode->values.node = node;
				break;
			}

			case QUOTE:
			{
				std::string result = parseString();
				if (!m_error.empty())
					return false;
				m_rootNode->key = result;
				break;
			}

			case SEMICOLON:
			{
				break;
			}
			default:
			{
				m_error = " an error occured between  at the position : "+std::to_string(m_positionJson) ;
			}
		}
		m_positionJson++;
	}
	return true;
}

bool JsonParser::parseBoolean()
{
	size_t nbrSizeBool = 4;
	if ( m_positionJson + nbrSizeBool < m_jsonSize)
	{
		std::string value;
		for (int i = 0; i < nbrSizeBool; i++)
			value = m_jsonStr[m_positionJson + i];
		if (value == "false")
			return false;
		else if (value == "true")
			return true;
		else
		{
			m_error += " Could not parse json bool between the position : [" + \
				std::to_string(m_positionJson -nbrSizeBool) + ", " + std::to_string(m_positionJson) + "] \n";
		}
		return false;
	}
	return false;


	JsonParser::TokenType type = UNKNOW;
	size_t prevPos = m_positionJson;
	m_positionJson++;
	std::string value;
	while (type != QUOTE
		&& type == UNKNOW
		&& m_positionJson < m_jsonSize)
	{
		type = getTokenType();
		value += m_jsonStr[m_positionJson];
		m_positionJson++;
	}
	if (getTokenType() != QUOTE)
	{
		m_error = " Could not parse json string between the position : [" + \
			std::to_string(prevPos) + ", " + std::to_string(m_positionJson) + "] \n";
		m_positionJson = prevPos;
	}

	return true;
}

std::vector<Node*> JsonParser::parseArray()
{
	std::vector<Node*> nodes;
	JsonParser::TokenType type = UNKNOW;
	bool isCompleted  = false;
	while (m_positionJson < m_jsonSize && m_error.empty() && !isCompleted)
	{
		switch (getTokenType())
		{
			///TODO
			case CURLY_CLOSE:
			{
				isCompleted = true;
				break;
			}
		}
		m_positionJson++;
	}
	
	return nodes;
}

JsonParser::~JsonParser()
{
}

void JsonParser::setNode(Node* node)
{
	//Get Key
	std::string key = parseString();
	if (!key.empty() || !m_error.empty())
		m_error = "An error occured by parsing key at the position" + std::to_string(m_positionJson);
	node->key = key;

	//GetValue
	bool isCompleted = false;
	while (m_positionJson < m_jsonSize && m_error.empty() && !isCompleted)
	{
		std::string error = "An error occured by trying to parse the value of the Key " + key;
		switch (getTokenType())
		{
			case CURLY_OPEN:
			{
				Node* node = parseNode();
				if (!node)
					m_error = " Could not parse json node at the position : " + std::to_string(m_positionJson);
				break;
				node->values.node = node;
				node->type = Node::Type::NODE;
			}

			case ARRAY_OPEN:
			{
				std::vector<Node*> nodes = parseArray();
				if (!m_error.empty())
					m_error = " could not parse json array at the position : " + std::to_string(m_positionJson);
				node->values.list = nodes;
				break;
			}

			case BOOL_TYPE:
			{
				bool result = parseBoolean();
				if (!m_error.empty())
					m_error += " Could not parse json bool at the position : " + std::to_string(m_positionJson);
				node->type = Node::Type::BOOLEAN;
				node->values.strValue = result;
				break;
			}
			case SEMICOLON:
			{
				break;
			}

			case COMMA:
			{
				break;
			}
			case NUMBER_TYPE:
			{
				node->values.fValue = parseNumber();
				node->type = Node::Type::FLOAT;
				break;
			}
			case QUOTE:
			{
				std::string result = parseString();
				if (!m_error.empty())
					m_error += error;
				node->type = Node::Type::STRING;
				node->values.strValue = result;
				break;
			}
			case CURLY_CLOSE:
			{
				isCompleted = true;
				break;
			}
			default:
			{
				m_error = " an error occured between  at the position : " + std::to_string(m_positionJson);
				break;
			}
		}
	}
}


Node* JsonParser::parseNode()
{
	//Create node
	Node* node = new Node;
	setNode(node);
	if (!m_error.empty())
	{
		delete node;
		return nullptr;
	}
	return node;

}

float JsonParser::parseNumber()
{
	std::string value;
	JsonParser::TokenType type = NUMBER_TYPE;
	while (type == NUMBER_TYPE)
	{
		type = getTokenType();
		value += m_jsonStr[m_positionJson];
		m_positionJson++;
	}
	return atof(value.c_str())
}

std::string JsonParser::parseString()
{
	JsonParser::TokenType type = UNKNOW;
	size_t prevPos = m_positionJson;
	m_positionJson++;
	std::string value;
	while (type != QUOTE 
		&& type == UNKNOW
		&& m_positionJson< m_jsonSize)
	{
		type = getTokenType();
		value += m_jsonStr[m_positionJson];
		m_positionJson++;
	}
	if (getTokenType() != QUOTE)
	{
		m_error += " Could not parse json string between the position : [" + \
					std::to_string(prevPos) +", "+std::to_string(m_positionJson)+"] \n";
		m_positionJson = prevPos;
	}
	return value;
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
	else if (jsonCharacter >= '0' && jsonCharacter <= '9' || jsonCharacter =='.')
	{
		return NUMBER_TYPE;
	}
	else
		return UNKNOW;
}