/*
Example : 1 + 2 * 3 => 7
Compare Example : 1 == 1.1 => 0 / 2 > 1 => 1

For the namespace it is used to encapsulate the functions that are used to calculate the result of the expression.
The main function is CommenCalculate, which takes the input expression in the form of a vector
For CommenCalculate, it is the main function that will be called by the caller, 
and it will call the other functions in the namespace to do the actual calculation.
Most of the code was code by ChatGPT actually
*/
#include <cmath>
#include <stack>
#include "Calculators.h"

namespace
{
     // Tok for normal tokens, Neg for unary minus (to distinguish from binary minus)
    enum class OpKind { Tok, Neg };

    struct Op
    {
        OpKind kind;
        Token tok;

        // if it is common token, tok is the token; if it is unary minus, tok is NUL
        static Op fromTok(Token t) { return {OpKind::Tok, t}; }
        static Op neg() { return {OpKind::Neg, NUL}; }
    };

    // OpInfo contains the precedence, associativity and arity of an operator
    struct OpInfo { int prec; bool rightAssoc; int arity; };

    static bool isFunc(Token t) { return t == SIN || t == COS || t == TAN || t == SQRT || t == ABS || t == LOG || t == LN || t == EXP; }
    static bool isValue(Token t) { return t == NUM; }
    static bool isUnaryTok(Token t) { return t == BANG; }

    static bool isBinaryTok(Token t)
    {
        switch (t)
        {
            case SQUA:
            case MULT: case DIVI: case MOD:
            case PLUS: case MINU:
            case GREATER: case GREATER_EQUAL:
            case LESS: case LESS_EQUAL:
            case EQUAL_EQUAL: case BANG_EQUAL:
            case AND: case OR:
                return true;
            default:
                return false;
        }
    }

    static OpInfo info(const Op& op)
    {
        // func > (!, unary-) [right] > pow [right] > */% > +- > cmp > eq > && > ||
        if (op.kind == OpKind::Tok && isFunc(op.tok)) return {9, false, 1};
        if (op.kind == OpKind::Neg) return {8, true, 1};
        if (op.kind == OpKind::Tok && op.tok == BANG) return {8, true, 1};

        if (op.kind == OpKind::Tok && op.tok == SQUA) return {7, true, 2};

        if (op.kind == OpKind::Tok && (op.tok == MULT || op.tok == DIVI || op.tok == MOD))
            return {6, false, 2};

        if (op.kind == OpKind::Tok && (op.tok == PLUS || op.tok == MINU))
            return {5, false, 2};

        if (op.kind == OpKind::Tok && (op.tok == GREATER || op.tok == GREATER_EQUAL || op.tok == LESS || op.tok == LESS_EQUAL))
            return {4, false, 2};

        if (op.kind == OpKind::Tok && (op.tok == EQUAL_EQUAL || op.tok == BANG_EQUAL))
            return {3, false, 2};

        if (op.kind == OpKind::Tok && op.tok == AND) return {2, false, 2};
        if (op.kind == OpKind::Tok && op.tok == OR)  return {1, false, 2};

        return {0, false, 0};
    }

    // isTruthy considers any number with absolute value less than 1e-12 as false,
    // and others as true as the number less than 1e-12 is considered as zero in the context of this calculator, it is reasonable to treat them as false
    static bool isTruthy(double x) { return std::fabs(x) > 1e-12; }

    static std::string toStr(double x)
    {
        if (std::fabs(x) < 1e-12) x = 0.0;
        return std::to_string(x);
    }

    // pop1 pops one value from the stack and stores it in a;
    // returns false if the stack is empty
    static bool pop1(std::stack<double>& st, double& a)
    {
        if (st.empty()) return false;
        a = st.top(); st.pop();
        return true;
    }

    // pop2 pops two values from the stack and stores them in a and b (b is the top, a is the second top); 
    // returns false if the stack has less than 2 values
    static bool pop2(std::stack<double>& st, double& a, double& b)
    {
        if (st.size() < 2) return false;
        b = st.top(); st.pop();
        a = st.top(); st.pop();
        return true;
    }

    // apply applies the operator op to the top values on the stack st,
    // using function and variables for function calls and variable lookups;
    // returns false if there is an error
    static bool apply(const Op& op, std::stack<double>& st,
                      Error& err)
    {
        // function: sin/cos/tan/sqrt/abs/log/ln/exp
        if (op.kind == OpKind::Tok && isFunc(op.tok))
        {
            double a;
            if (!pop1(st, a)) { err = ERROR_SYNTAX_ERROR; return false; }
            switch (op.tok)
            {
                case SIN: st.push(std::sin(a)); return true;
                case COS: st.push(std::cos(a)); return true;
                case TAN: st.push(std::tan(a)); return true;
                case SQRT:
                    if (a < -1e-12) { err = ERROR_INVALID_ARGUMENT; return false; }
                    st.push(std::sqrt(a));
                    return true;
                case ABS: st.push(std::fabs(a)); return true;
                case LOG:
                    if (a < 1e-12) { err = ERROR_INVALID_ARGUMENT; return false; }
                    st.push(std::log10(a));
                    return true;
                case LN:
                    if (a < 1e-12) { err = ERROR_INVALID_ARGUMENT; return false; }
                    st.push(std::log(a));
                    return true;
                case EXP: st.push(std::exp(a)); return true;
                default: err = ERROR_UNKNOWN_ERROR; return false;
            }
        }

        // unary -
        if (op.kind == OpKind::Neg)
        {
            double a;
            if (!pop1(st, a)) { err = ERROR_SYNTAX_ERROR; return false; }
            st.push(-a);
            return true;
        }

        // !
        if (op.kind == OpKind::Tok && op.tok == BANG)
        {
            double a;
            if (!pop1(st, a)) { err = ERROR_SYNTAX_ERROR; return false; }
            st.push(isTruthy(a) ? 0.0 : 1.0);
            return true;
        }

        // binary
        if (op.kind != OpKind::Tok) { err = ERROR_UNKNOWN_ERROR; return false; }

        double a, b;
        if (!pop2(st, a, b)) { err = ERROR_SYNTAX_ERROR; return false; }

        switch (op.tok)
        {
            case PLUS: st.push(a + b); return true;
            case MINU: st.push(a - b); return true;
            case MULT: st.push(a * b); return true;

            case DIVI:
                if (std::fabs(b) < 1e-12) { err = ERROR_DIVISION_BY_ZERO; return false; }
                st.push(a / b);
                return true;

            case MOD:
                if (std::fabs(b) < 1e-12) { err = ERROR_MODULO_BY_ZERO; return false; }
                st.push(std::fmod(a, b));
                return true;

            case SQUA:
                st.push(std::pow(a, b));
                return true;

            case GREATER:       st.push(a >  b ? 1.0 : 0.0); return true;
            case GREATER_EQUAL: st.push(a >= b ? 1.0 : 0.0); return true;
            case LESS:          st.push(a <  b ? 1.0 : 0.0); return true;
            case LESS_EQUAL:    st.push(a <= b ? 1.0 : 0.0); return true;
            case EQUAL_EQUAL:   st.push(a == b ? 1.0 : 0.0); return true;
            case BANG_EQUAL:    st.push(a != b ? 1.0 : 0.0); return true;

            case AND: st.push((isTruthy(a) && isTruthy(b)) ? 1.0 : 0.0); return true;
            case OR:  st.push((isTruthy(a) || isTruthy(b)) ? 1.0 : 0.0); return true;

            default:
                err = ERROR_SYNTAX_ERROR;
                return false;
        }
    }
    
    // operandLike returns true if the token can be an operand (number, variable or closing parenthesis), 
    // which is used to determine if a minus sign is unary or binary
    static bool operandLike(Token t)
    {
        return t == NUM || t == RPARE || t == PARAM;
    }
}

std::string CommenCalculate(const std::vector<std::pair<Token, std::string>> input,
                            const std::vector<std::pair<Token, std::string>> function,
                            const std::map<std::string, double> variables)
{
    if (input.empty())
        return GetErrorMessage(ERROR_EMPTY_INPUT);

    // store the output of the shunting yard algorithm before evaluation
    struct Rpn
    {
        bool isNum;
        std::string lex;
        Op op;
        static Rpn num(std::string s) { return {true, std::move(s), Op::fromTok(NUL)}; }
        static Rpn oper(Op o) { Rpn r; r.isNum = false; r.op = o; return r; }
    };

    std::vector<Rpn> out;
    std::stack<Op> ops;
    
    auto popByPrec = [&](const Op& cur)
    {
        OpInfo curi = info(cur);
        while (!ops.empty())
        {
            Op top = ops.top();
            if (top.kind == OpKind::Tok && top.tok == LPARE) break;

            OpInfo topi = info(top);
            bool shouldPop =
                (!curi.rightAssoc && curi.prec <= topi.prec) ||
                (curi.rightAssoc  && curi.prec <  topi.prec);

            if (!shouldPop) break;

            out.push_back(Rpn::oper(top));
            ops.pop();
        }
    };

    Token prev = UNKNOWN;
    bool hasPrev = false;
    bool sawAnyToken = false;

    // check errors and convert to RPN using the shunting yard algorithm
    for (size_t i = 0; i < input.size(); ++i)
    {
        Token t = input[i].first;
        const std::string& lex = input[i].second;

        if (t == END) break;
        sawAnyToken = true;

        if (t == UNKNOWN || t == NUL)
            return GetErrorMessage(ERROR_SYNTAX_ERROR);

        if (t == VAR || t == FUN)
            return GetErrorMessage(ERROR_INVALID_ARGUMENT);

        if (isValue(t))
        {
            out.push_back(Rpn::num(lex));
            prev = t; hasPrev = true;
            continue;
        }

        if (t == PARAM)
        {
            auto it = variables.find(lex);
            if (it == variables.end())
                return GetErrorMessage(ERROR_UNDEFINED_VARIABLE);

            out.push_back(Rpn::num(std::to_string(it->second)));
            prev = t; hasPrev = true;
            continue;
        }

        if (isFunc(t))
        {
            ops.push(Op::fromTok(t));
            prev = t; hasPrev = true;
            continue;
        }

        if (t == LPARE)
        {
            ops.push(Op::fromTok(LPARE));
            prev = t; hasPrev = true;
            continue;
        }

        if (t == RPARE)
        {
            bool matched = false;
            while (!ops.empty())
            {
                if (ops.top().kind == OpKind::Tok && ops.top().tok == LPARE)
                {
                    matched = true;
                    ops.pop();
                    break;
                }
                out.push_back(Rpn::oper(ops.top()));
                ops.pop();
            }
            if (!matched)
                return GetErrorMessage(ERROR_MISSING_PARENTHESIS);

            if (!ops.empty() && ops.top().kind == OpKind::Tok && isFunc(ops.top().tok))
            {
                out.push_back(Rpn::oper(ops.top()));
                ops.pop();
            }

            prev = t; hasPrev = true;
            continue;
        }

        if (t == MINU)
        {
            bool unary = true;
            if (hasPrev && operandLike(prev)) unary = false;

            Op cur = unary ? Op::neg() : Op::fromTok(MINU);
            popByPrec(cur);
            ops.push(cur);

            prev = t; hasPrev = true;
            continue;
        }

        if (isUnaryTok(t))
        {
            Op cur = Op::fromTok(BANG);
            popByPrec(cur);
            ops.push(cur);

            prev = t; hasPrev = true;
            continue;
        }

        if (isBinaryTok(t))
        {
            Op cur = Op::fromTok(t);
            popByPrec(cur);
            ops.push(cur);

            prev = t; hasPrev = true;
            continue;
        }

        return GetErrorMessage(ERROR_SYNTAX_ERROR);
    }

    if (!sawAnyToken)
        return GetErrorMessage(ERROR_EMPTY_INPUT);

    while (!ops.empty())
    {
        if (ops.top().kind == OpKind::Tok && ops.top().tok == LPARE)
            return GetErrorMessage(ERROR_MISSING_PARENTHESIS);
        out.push_back(Rpn::oper(ops.top()));
        ops.pop();
    }

    std::stack<double> st;
    for (const auto& it : out)
    {
        if (it.isNum)
        {
            st.push(getNum(it.lex));
            continue;
        }

        Error err = ERROR_UNKNOWN_ERROR;
        if (!apply(it.op, st, err))
            return GetErrorMessage(err);
    }

    if (st.size() != 1)
        return GetErrorMessage(ERROR_SYNTAX_ERROR);

    return toStr(st.top());
}