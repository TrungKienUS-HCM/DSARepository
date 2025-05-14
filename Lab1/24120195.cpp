// NGUYEN DINH TRUNG KIEN - 24CTT3 - 24120195
// LAB 1 - BIG INTEGER EVALUATION
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
using namespace std;

// FUNCTIONS DECLARATION
int precedence(char s);
bool higherPrecedence(char s1, char s2);
bool isNum(char s);
bool isOperator(char s);
void eraseZero(string& s);
bool checkExpression(string exp);
int charToInt(char s);
string intToStr(int s);
bool isNegative(string s);
void bigNumAbs(string& s);
int biggerNum(string num1, string num2);
string bigNumAdd(string op1, string op2);
string bigNumSubtract(string op1, string op2);
bool isZero(string s);
void addZero(string& num, int n);
string changeNumSign(string s);
string bigNumMultiply(string op1, string op2);
string getQuotion(string op1, string op2, string& res);
string bigNumDivide(string op1, string op2);
string numbersCalculate(string n1, string n2, char op);
string expressionCalculate(string exp);

// FUNCTIONS DEFINITION

int precedence(char s)
{
	if (s == '*' || s == '/')
	{
		return 2;
	}
	if (s == '+' || s == '-')
	{
		return 1;
	}
	return 0;
}

bool higherPrecedence(char s1, char s2)
{
	return precedence(s1) >= precedence(s2);
}

bool isNum(char s)
{
	return s - '0' >= 0 && s - '0' <= 9;
}

bool isOperator(char s)
{
	return s == '+' || s == '-' || s == '*' || s == '/';
}

void eraseZero(string& s)
{
	bool changeSign = false;
	if (isNegative(s)) changeSign = true;
	bigNumAbs(s);
	while ((int)s.length() > 1 && s[0] == '0')
	{
		s.erase(0, 1);
	}
	if (changeSign) s = changeNumSign(s);
}

bool checkExpression(string exp)
{
	int prevCheck = 0, postCheck = (int)exp.length() - 1;
	while (exp[prevCheck] == ' ') prevCheck++;
	while (exp[postCheck] == ' ') postCheck--;
	if (exp[prevCheck] != '(' && exp[prevCheck] != '-' && !isNum(exp[prevCheck])) return false;
	if (exp[postCheck] != ')' && !isNum(exp[postCheck])) return false;
	
	stack<char> checkParenthesis;
	// number: true, operator: false
	bool checkNumOp = false;
	int i = 0;
	while (i < (int)exp.length())
	{
		if (exp[i] != ' ')
		{
			if (!isNum(exp[i]) && !isOperator(exp[i]) && exp[i] != '(' && exp[i] != ')') return false;
			if (exp[i] == '(')
			{
				if (checkNumOp) return false;
				checkParenthesis.push('(');
			}
			else if (exp[i] == ')')
			{
				if (!checkNumOp) return false;
				if (checkParenthesis.empty() || checkParenthesis.top() != '(')
				{
					return false;
				}
				checkParenthesis.pop();
			}
			else
			{
				if (exp[i] == '-')
				{
					int checkRight = i + 1;
					for (; checkRight < (int)exp.length(); checkRight++)
					{
						if (exp[checkRight] != ' ') break;
					}
					if ((isOperator(exp[checkRight]) || exp[checkRight] != '(') && !isNum(exp[checkRight])) return false;

					if (!checkNumOp && i > 0)
					{
						int checkLeft = i - 1;
						for (; checkLeft >= 0; checkLeft--)
						{
							if (exp[checkLeft] != ' ') break;
						}
						if (exp[checkLeft] != '(') return false;
					}

					if (checkNumOp)
					{
						checkNumOp = false;
					}
					else
					{
						checkNumOp = true;
						++i;
						while (exp[i] == ' ') ++i;
						while (isNum(exp[i]) && i < (int)exp.length()) ++i;
						continue;
					}
				}
				else if (isOperator(exp[i]))
				{
					if (!checkNumOp)
					{
						return false;
					}
					checkNumOp = false;
				}
				else if (isNum(exp[i]))
				{
					if (checkNumOp)
					{
						return false;
					}
					checkNumOp = true;
					while (isNum(exp[i]) && i < (int)exp.length()) ++i;
					continue;
				}
			}
		}
		++i;
	}
	if (!checkParenthesis.empty()) return false;
	return true;
}

int charToInt(char s)
{
	return s - '0';
}

string intToStr(int s)
{
	if (s == 0) return "0";
	string res;
	bool negative = false;
	if (s < 0) negative = true;
	while (s > 0)
	{
		res = (char)(abs(s) % 10 + '0') + res;
		s /= 10;
	}
	if (negative) return '-' + res;
	return res;
}

bool isNegative(string s)
{
	if (s.length() <= 0) return false;
	return s[0] == '-';
}

void bigNumAbs(string& s)
{
	if (isNegative(s))
	{
		s = changeNumSign(s);
	}
}

int biggerNum(string num1, string num2)
{
	eraseZero(num1);
	eraseZero(num2);
	if (isNegative(num1))
	{
		if (isNegative(num2))
		{
			return biggerNum(changeNumSign(num2), changeNumSign(num1));
		}
		else
		{
			return -1;
		}
	}
	else
	{
		if (isNegative(num2))
		{
			return 1;
		}
	}
	if (num1.length() < num2.length())
	{
		return -1;
	}
	else
	{
		if (num1.length() > num2.length())
		{
			return 1;
		}
		for (int i = 0; i < num1.length(); ++i)
		{
			if (num1[i] > num2[i]) return 1;
			if (num1[i] < num2[i]) return -1;
		}
	}
	return 0;
}

string bigNumAdd(string op1, string op2)
{
	eraseZero(op1);
	eraseZero(op2);
	if (isNegative(op1))
	{
		if (isNegative(op2))
		{
			return bigNumSubtract(op1, changeNumSign(op2));
		}
		else
		{
			return bigNumSubtract(op2, changeNumSign(op1));
		}
	}
	else
	{
		if (isNegative(op2))
		{
			return bigNumSubtract(op1, changeNumSign(op2));
		}
	}
	string res;
	int i = (int)op1.length() - 1, j = (int)op2.length() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0)
	{
		int o1 = 0, o2 = 0;
		if (i >= 0) o1 = charToInt(op1[i]);
		if (j >= 0) o2 = charToInt(op2[j]);
		int tmpAdd = o1 + o2 + carry;
		carry = tmpAdd / 10;
		res = intToStr(tmpAdd % 10) + res;
		--i; --j;
	}
	if (carry > 0) res = intToStr(carry) + res;
	return res;
}

string bigNumSubtract(string op1, string op2)
{
	eraseZero(op1);
	eraseZero(op2);
	if (isNegative(op1))
	{
		op1.erase(0, 1);
		if (isNegative(op2))
		{
			op2.erase(0, 1);
			return changeNumSign(bigNumSubtract(op1, op2));
		}
		else
		{
			return changeNumSign(bigNumAdd(op1, op2));
		}
	}
	else
	{
		if (isNegative(op2))
		{
			op2.erase(0, 1);
			return bigNumAdd(op1, op2);
		}
	}
	if (biggerNum(op2, op1) == 1) return changeNumSign(bigNumSubtract(op2, op1));
	string res;
	int i = (int)op1.length() - 1, j = (int)op2.length() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0)
	{
		int o1 = 0, o2 = 0;
		if (i >= 0) o1 = charToInt(op1[i]);
		if (j >= 0) o2 = charToInt(op2[j]);
		int tmpMinus = o1 - o2 - carry;
		if (tmpMinus < 0)
		{
			tmpMinus += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res = intToStr(tmpMinus) + res;
		--i; --j;
	}
	eraseZero(res);
	return res;
}

bool isZero(string s)
{
	for (int i = 0; i < (int)s.length(); ++i)
	{
		if (s[i] != '0')
			return false;
	}
	return true;
}

void addZero(string& num, int n)
{
	while (n--)
	{
		num += '0';
	}
}

string changeNumSign(string s)
{
	if (isNegative(s))
	{
		s.erase(0, 1);
	}
	else
	{
		s = '-' + s;
	}
	return s;
}

string bigNumMultiply(string op1, string op2)
{
	eraseZero(op1);
	eraseZero(op2);
	if (op2.length() > op1.length()) return bigNumMultiply(op2, op1);
	if (op1 == "0" || op2 == "0") return "0";
	bool changeSign = false;
	if (isNegative(op1)) changeSign = !changeSign;
	if (isNegative(op2)) changeSign = !changeSign;

	bigNumAbs(op1); bigNumAbs(op2);
	string res = "0";
	int i = (int)op2.length() - 1;
	for(; i >= 0; --i)
	{
		int j = (int)op1.length() - 1;
		string tmpMul = "0";
		for (; j >= 0; --j)
		{
			int tmpRes = charToInt(op1[j]) * charToInt(op2[i]);
			string tmpOp = intToStr(tmpRes);
			addZero(tmpOp, (int)op1.length() - j - 1);
			tmpMul = bigNumAdd(tmpMul, tmpOp);
		}
		addZero(tmpMul, (int)op2.length() - i - 1);
		res = bigNumAdd(res, tmpMul);
	}
	if (changeSign) return changeNumSign(res);
	return res;
}

string getQuotion(string op1, string op2, string& res)
{
	eraseZero(op1);
	eraseZero(op2);
	int mul = -1;
	string tmpCmp;
	for (; mul < 10; ++mul)
	{
		tmpCmp = bigNumMultiply(op2, intToStr(mul + 1));
		if (biggerNum(tmpCmp, op1) > 0)
		{
			break;
		}
	}
	res += intToStr(mul);
	return bigNumMultiply(op2, intToStr(mul));
}

string bigNumDivide(string op1, string op2)
{
	eraseZero(op1);
	eraseZero(op2);
	if (isZero(op2))
	{
		return "Error";
	}
	if (isZero(op1))
	{
		return "0";
	}
	if (op2 == "1")
	{
		return op1;
	}
	bool changeSign = false;
	if (isNegative(op1)) changeSign = !changeSign;
	if (isNegative(op2)) changeSign = !changeSign;
	bigNumAbs(op1);
	bigNumAbs(op2);
	if (biggerNum(op2, op1) == 1) return "0";

	string res, remainder;
	string tmpDiv;
	int finished = 0;
	do
	{
		finished++;
		tmpDiv = op1.substr(0, finished);
	} while (biggerNum(tmpDiv, op2) < 0);
	remainder = tmpDiv;
	for (; finished <= (int)op1.length(); finished++)
	{
		string tmpDivided = getQuotion(remainder, op2, res);
		remainder = bigNumSubtract(remainder, tmpDivided);
		remainder += op1[finished];
	}
	if (changeSign) return changeNumSign(res);
	return res;
}

string numbersCalculate(string n1, string n2, char op)
{
	if (n1.empty() || n2.empty()) return "";
	switch (op)
	{
		case '+': { return bigNumAdd(n1, n2); }
		case '-': { return bigNumSubtract(n1, n2); }
		case '*': { return bigNumMultiply(n1, n2); }
		case '/': { return bigNumDivide(n1, n2); }
	}
	return "";
}

string expressionCalculate(string exp)
{
	if (!checkExpression(exp)) return "Error";
	stack<string> numbers;
	stack<char> operators;
	bool checkMinus = false;

	int i = 0;
	while (i < (int)exp.length())
	{
		if (exp[i] != ' ')
		{
			if (exp[i] == '(')
			{
				operators.push('(');
			}
			else if (exp[i] == ')')
			{
				while (!operators.empty() && operators.top() != '(')
				{
					char op = operators.top();
					operators.pop();

					string n2 = numbers.top();
					numbers.pop();

					string n1 = numbers.top();
					numbers.pop();

					string res = numbersCalculate(n1, n2, op);
					if (res == "Error") return "Error";
					numbers.push(res);
				}

				operators.pop();
			}
			else if (isNum(exp[i]) || (exp[i] == '-' && !checkMinus))
			{
				string tmpNum;
				tmpNum += exp[i++];
				while (exp[i] == ' ') i++;
				while (isNum(exp[i]))
				{
					tmpNum += exp[i++];
				}
				checkMinus = true;
				numbers.push(tmpNum);
				continue;
			}
			else
			{
				while (!operators.empty() && higherPrecedence(operators.top(), exp[i]))
				{
					char op = operators.top();
					operators.pop();

					string n2 = numbers.top();
					numbers.pop();

					string n1 = numbers.top();
					numbers.pop();

					string res = numbersCalculate(n1, n2, op);
					if (res == "Error") return "Error";
					numbers.push(res);
				}

				operators.push(exp[i]);
				checkMinus = false;
			}
		}
		++i;
	}

	while (!operators.empty())
	{
		char op = operators.top();
		operators.pop();

		string n2 = numbers.top();
		numbers.pop();

		string n1 = numbers.top();
		numbers.pop();

		string res = numbersCalculate(n1, n2, op);
		if (res == "Error") return "Error";
		numbers.push(res);
	}

	return numbers.top();
}

int main(int argc, char* argv[])
{
	ifstream getExp(argv[1]);
	ofstream printRes(argv[2]);

	if (!getExp.is_open())
	{
		cout << "Cannot open input file" << endl;
	}
	if (!printRes.is_open())
	{
		cout << "Cannot open output file" << endl;
	}

	string expression;
	while (getline(getExp, expression))
	{
		string result = expressionCalculate(expression);
		printRes << result << endl;
		cout << result << endl;
	}

	getExp.close();
	printRes.close();
}
