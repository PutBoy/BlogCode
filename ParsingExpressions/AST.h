#pragma once

#include <vector>
#include <memory>

#include "Node.h"
#include "Token.h"
#include <exception>

std::shared_ptr<Node> pop(std::vector<std::shared_ptr<Node>>& stack)
{
	auto ret = stack.back();
	stack.pop_back();
	return ret;
}

std::shared_ptr<Node> makeNewBinary(Token token, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
{
	switch (token.token.op)
	{
	case (Token::Add) :
		return std::make_shared<Add>(left, right);
	case (Token::Sub) :
		return std::make_shared<Sub>(left, right);
	case (Token::Mul) :
		return std::make_shared<Mul>(left, right);
	case (Token::Div) :
		return std::make_shared<Div>(left, right);
	}
	return nullptr;  //should never ever ever happen.
}

std::shared_ptr<Node> makeNewUnary(Token token, std::shared_ptr<Node> left)
{
	switch (token.token.op)
	{
	case (Token::Pos) :
		return std::make_shared<Pos>(left);
	case (Token::Neg) :
		return std::make_shared<Neg>(left);
	}
	return nullptr;  //should never ever ever happen.
}

std::shared_ptr<Node> makeTree(const std::vector<Token>& queue)
{
	std::vector<std::shared_ptr<Node>> stack;

	for (auto token : queue)
	{
		if (token.type == Token::Type::Operator)
		{
			bool unary = (token.token.op == Token::OpType::Pos ||
				token.token.op == Token::OpType::Neg);
			if (unary)
			{
				auto left = pop(stack);
				auto node = makeNewUnary(token, left);
				if (node)
					stack.push_back(node);
				else
				{
					stack.clear();
					break;
				}
			}
			else
			{
				auto right = pop(stack);
				auto left = pop(stack);
				auto node = makeNewBinary(token, left, right);
				if (node)
					stack.push_back(node);
				else
				{
					stack.clear();
					break;
				}
			}
		}
		else
		{
			stack.push_back(std::make_shared<Number>(token.token.value));
		}
	}
	return stack.back();
}

std::string prettyNodes(std::vector<std::string> row, int spacing)
{
	std::string ret;

	std::string fill(spacing / 2, ' ');
	ret += fill;
	for (auto riter = row.rbegin(); riter != row.rend(); ++riter)
	{
		std::string fill(spacing - riter->size(), ' ');
		ret += *riter + fill;
	}
	return std::move(ret);
}

std::string prettyEdges(std::vector<std::string> row, int spacing)
{
	std::string ret;
	std::string fill(spacing / 2, ' ');
	ret += fill;
	for (auto riter = row.rbegin(); riter != row.rend(); ++riter)
	{
		std::string fill(spacing - riter->size() , ' ');
		ret += *riter + fill;
	}
	return std::move(ret);
}


std::string pretty(std::shared_ptr<Node> node)
{
	int depth = node->getDepth(0);
	int level = depth;
	std::string ret;

	std::vector<std::shared_ptr<Node>> currentLevel, nextLevel;

	currentLevel.push_back(node);
	std::vector<std::string> nodes;
	std::vector<std::string> edges;
	while (!currentLevel.empty()) {
		auto currNode = currentLevel.front();
		bool isOccupied = false;
		if (currNode == nullptr)
		{
			nodes.push_back("");
		}
		else
			nodes.push_back(currNode->toString());

		currentLevel.erase(currentLevel.begin());
		if (currNode) {

			if (currNode->getRight())
				edges.push_back("|");
			else
				edges.push_back("");
			if (currNode->getLeft())
				edges.push_back("|");
			else
				edges.push_back("");
			

			nextLevel.push_back(currNode->getRight());
			nextLevel.push_back(currNode->getLeft());

			isOccupied = true;
		}
		else
		{
			edges.push_back("");
			edges.push_back("");

			nextLevel.push_back(nullptr);
			nextLevel.push_back(nullptr);
		}
		if (currentLevel.empty()) {

			ret += prettyNodes(nodes, std::pow(2, level)) + "\n";
			ret += prettyEdges(edges, std::pow(2, (level - 1))) + "\n";
			
			nodes.clear();
			edges.clear();
			swap(currentLevel, nextLevel);
			--level;
			if (level <= 0)
				currentLevel.clear();
		}
	}
	return std::move(ret);
}