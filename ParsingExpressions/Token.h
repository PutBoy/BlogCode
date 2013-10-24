#pragma once

struct Token
{
	enum Type { Operator, Number };
	Type type;
	enum OpType { Add, Sub, Pos, Neg, Mul, Div, LParen, RParen };
	union
	{
		int value;
		OpType op;
	} token;
};