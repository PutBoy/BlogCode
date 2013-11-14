#include <memory>
#include <algorithm>
#include "Token.h"

class Node
{
public:
	virtual ~Node() {};

	virtual int evaluate() const = 0;
	virtual int getDepth(int current) const = 0;
	virtual std::string toString() const = 0;

	virtual std::shared_ptr<Node> getLeft() const { return nullptr; };
	virtual std::shared_ptr<Node> getRight() const { return nullptr; };

};

class BinaryOperator : public Node
{
public:
	BinaryOperator(std::shared_ptr<Node> left_, std::shared_ptr<Node> right_)
		:left(left_), right(right_) {}

	int getDepth(int current) const
	{
		return std::max(left->getDepth(current + 1), right->getDepth(current + 1));
	}

	std::shared_ptr<Node> getLeft() const { return left; };
	std::shared_ptr<Node> getRight() const { return right; };

protected:
	const std::shared_ptr<Node> left;
	const std::shared_ptr<Node> right;
};

class UnaryOperator : public Node
{
public:
	UnaryOperator(std::shared_ptr<Node> left_)
		:left(left_) {}

	int getDepth(int current) const
	{
		return left->getDepth(current + 1);
	}

	std::shared_ptr<Node> getLeft() const { return left; };

protected:
	const std::shared_ptr<Node> left;
};

class Number : public Node
{
public:
	Number(int value_)
		:value(value_) {}

	int getDepth(int current) const
	{
		return current + 1;
	}
	
	int evaluate() const
	{
		return value;
	}
	 
	std::string toString() const
	{
		return std::to_string(value);
	}

private:
	const int value;
};

class Pos : public UnaryOperator
{
public:
	Pos(std::shared_ptr<Node> left_)
	:UnaryOperator(left_)
	{}

	int evaluate() const
	{
		return left->evaluate();
	}

	std::string toString() const
	{
		return "+";
	}
};

class Neg : public UnaryOperator
{
public:
	Neg(std::shared_ptr<Node> left_)
		:UnaryOperator(left_)
	{}

	int evaluate() const
	{
		return -left->evaluate();
	}

	std::string toString() const
	{
		return "-";
	}
};

class Add : public BinaryOperator
{
public:
	Add(std::shared_ptr<Node> left_, std::shared_ptr<Node> right_)
		:BinaryOperator(left_, right_)
	{}

	int evaluate() const
	{
		return left->evaluate() + right->evaluate();
	}

	std::string toString() const
	{
		return "+";
	}
};

class Sub : public BinaryOperator
{
public:
	Sub(std::shared_ptr<Node> left_, std::shared_ptr<Node> right_)
	:BinaryOperator(left_, right_)
	{}

	int evaluate() const
	{
		return left->evaluate() - right->evaluate();
	}

	std::string toString() const
	{
		return "-";
	}
};

class Mul : public BinaryOperator
{
public:
	Mul(std::shared_ptr<Node> left_, std::shared_ptr<Node> right_)
	:BinaryOperator(left_, right_)
	{}

	int evaluate() const
	{
		return left->evaluate() * right->evaluate();
	}

	std::string toString() const
	{
		return "*";
	}
};

class Div : public BinaryOperator
{
public:
	Div(std::shared_ptr<Node> left_, std::shared_ptr<Node> right_)
	:BinaryOperator(left_, right_)
	{}

	int evaluate() const
	{
		return left->evaluate() / right->evaluate();
	}

	std::string toString() const
	{
		return "/";
	}
};

