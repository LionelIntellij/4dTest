#include <string>
#include <vector>
#include <map>



typedef  struct Node {
	Node* node;
	std::vector<Node*> list;
	bool bValue;
	float fValue;
	std::string strValue;
} Node;


class JsonParser
{
	enum TokenType
	{
		CURLY_OPEN,
		CURLY_CLOSE,
		ARRAY_OPEN,
		ARRAY_CLOSED,
		QUOTE,
		COMMA,
		UNKNOW
	};

public:
	JsonParser(const std::string & jsonStr);
	bool parse();
	std::string getError();

private:
	TokenType getTokenType();

private:
	std::string m_jsonStr;
	std::string m_error;
	std::map<std::string, Node*> m_json;
	size_t m_positionJson;
	size_t m_jsonSize;


};