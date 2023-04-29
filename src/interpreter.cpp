#include "headers\interpreter.h"

LiteralNode* getLiteral(std::string value, BlockNode* parent)
{
	// First search if there is a variable
	if(parent->hasVariable(value))
		return parent->getVariable(value);

	Type type = findDataType(value);
	if(type == Type::NULO)
		return nullptr;

	LiteralNode* literal = new LiteralNode();
	literal->value = value;
	literal->isAttachedToVariable = false;
	literal->type = type;
}

ArithmeticOperator* generateArithmeticOperator(std::string str, BlockNode* parent, std::string& fileName, int &lineNumber)
{
	ArithmeticOperator* root = new ArithmeticOperator();

	std::string lHalf;
	std::string rHalf;

	int	lastPrecedenceOperatorIndex	= -1;
	int	lastPrecedenceOperatorLevel	= 0;
	unsigned int strLenght	= str.size();
	for(unsigned int i = 0; i <	strLenght;	i++)
	{
		if(str[i] == '^')
			lastPrecedenceOperatorIndex	= i;
	}
	for(unsigned int i = 0; i <	strLenght;	i++)
	{
		if(str[i] == '*' || str[i] == '/' || str[i] == '%')
			lastPrecedenceOperatorIndex	= i;
	}
	for(unsigned int i = 0; i <	strLenght;	i++)
	{
		if(str[i] == '+' || str[i] == '-')
			lastPrecedenceOperatorIndex	= i;
	}

	if(lastPrecedenceOperatorIndex == -1)
	{
		#if DEBUG_SHOW_MATH_EXPRESSION_EVAL
		std::cout << "Error at: \"" << str << "\"" << std::endl;
		#endif
		ThrowException(SyntaxError, fileName, lineNumber, "Expressão não possui nenhum operador");
	}
	
	lHalf = trim(str.substr(0, lastPrecedenceOperatorIndex));
	char op = str[lastPrecedenceOperatorIndex];
	rHalf = trim(str.substr(lastPrecedenceOperatorIndex+1, strLenght));

	#if DEBUG_SHOW_MATH_EXPRESSION_EVAL
	std::cout << "{math} left half: " << lHalf << std::endl;
	std::cout << "{math} operator: " << op << std::endl;
	std::cout << "{math} right half: " << rHalf << std::endl;
	#endif

	root->op = op;

	if(lHalf.find_first_of("+-*/%^") != std::string::npos)
	{
		#if DEBUG_SHOW_MATH_EXPRESSION_EVAL
		std::cout << "{expression} re-tree: \"" << lHalf << "\" (" << lHalf.find_first_of("+-*/%^") << ")" << std::endl;
		#endif
		root->left = generateArithmeticOperator(lHalf, parent, fileName, lineNumber);
	}
	else
	{
		LiteralNode* literal = getLiteral(lHalf, parent);
		if(literal == nullptr)
			ThrowException(SyntaxError, fileName, lineNumber, "Nome \"" + lHalf + "\" não existe nesse contexto");
		root->left = literal;
	}

	if(rHalf.find_first_of("+-*/%^") != std::string::npos)
	{
		#if DEBUG_SHOW_MATH_EXPRESSION_EVAL
		std::cout << "{math} re-tree: \"" << rHalf << "\" (" << rHalf.find_first_of("+-*/%^") << ")" << std::endl;
		#endif
		root->right = generateArithmeticOperator(rHalf, parent, fileName, lineNumber);
	}
	else
	{
		LiteralNode* literal = getLiteral(rHalf, parent);
		if(literal == nullptr)
			ThrowException(SyntaxError, fileName, lineNumber, "Nome \"" + rHalf + "\" não existe nesse contexto");
		root->right = literal;
	}

	#if DEBUG_SHOW_MATH_EXPRESSION_EVAL
	LiteralNode* result = root->result();
	std::cout << "{math} result: \"" << result->value << "\"" << std::endl;
	delete result;
	#endif

	return root;
}

void implementIf(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber, std::unordered_map<unsigned int, BlockNode*>& tabtable, int tabLevel)
{
	IfNode* node = new IfNode();
	tabtable[tabLevel + 1] = node;
	parent->addChild(node);
}