#include <string>
#include <vector>
#include <map>



typedef  struct Node {
	enum Type {
		NODE,
		BOOLEAN,
		STRING,
		FLOAT,
	};

	Node() {};
	//TODO copy constructor necessary
	std::string key;
	union Value {
		Node* node;
		std::vector<Node*> list;
		bool bValue;
		float fValue;
		std::string strValue;
	}values;
	Type type;
	~Node() =default;
} Node;




class JsonParser
{
	enum TokenType
	{
		CURLY_OPEN,
		CURLY_CLOSE,
		ARRAY_OPEN,
		ARRAY_CLOSE,
		SEMICOLON,
		QUOTE,
		COMMA,
		BOOL_TYPE,
		NUMBER_TYPE,
		UNKNOW
	};

public:
	JsonParser(const std::string & jsonStr);
	bool parse();
	std::string getError();
	~JsonParser();

private:
	TokenType getTokenType();
	std::string parseString();
	bool parseBoolean();
	std::vector<Node*> parseArray();
	float parseNumber();
	Node* parseNode();
	void setNode(Node* node);

private:
	std::string m_jsonStr;
	std::string m_error;
	Node* m_rootNode;
	size_t m_positionJson;
	size_t m_jsonSize;
	std::string m_KeyRoot;


};