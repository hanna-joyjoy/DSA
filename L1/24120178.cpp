
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;


struct BigInt 
{
    string digits;
    bool isNegative;

    BigInt() 
    {
        digits = "0";
        isNegative = false;
    }

    BigInt(string s) 
    {
        isNegative = false;
        if (!s.empty() && s[0] == '-') 
        {
            isNegative = true;
            s = s.substr(1);
        }

        while (s.size() > 1 && s[0] == '0') s.erase(0, 1);
        digits = s.empty() ? "0" : s;
        reverse(digits.begin(), digits.end());
    }

    BigInt(int x) 
    {
        isNegative = (x < 0);
        x = abs(x);
        if (x == 0) digits = "0";
        while (x > 0) 
        {
            digits += (x % 10) + '0';
            x /= 10;
        }
    }

    void trim() 
    {
        while (digits.size() > 1 && digits.back() == '0')
            digits.pop_back();
        if (digits == "0") isNegative = false;
    }

    void print() const 
    {
        if (isNegative && digits != "0") cout << "-";
        for (int i = digits.size() - 1; i >= 0; i--) cout << digits[i];
        cout << endl;
    }

    string toString() const 
    {
        string s = digits;
        reverse(s.begin(), s.end());
        return (isNegative && s != "0" ? "-" : "") + s;
    }

    static bool absLessThan(const BigInt& a, const BigInt& b) 
    {
        if (a.digits.size() != b.digits.size())
            return a.digits.size() < b.digits.size();
        for (int i = a.digits.size() - 1; i >= 0; --i) 
        {
            if (a.digits[i] != b.digits[i])
                return a.digits[i] < b.digits[i];
        }
        return false;
    }

    static BigInt absAdd(const BigInt& a, const BigInt& b) 
    {
        BigInt result;
        int carry = 0;
        result.digits = "";

        for (int i = 0; i < max(a.digits.size(), b.digits.size()) || carry; ++i) 
        {
            int d1 = i < a.digits.size() ? a.digits[i] - '0' : 0;
            int d2 = i < b.digits.size() ? b.digits[i] - '0' : 0;
            int sum = d1 + d2 + carry;
            result.digits += (sum % 10) + '0';
            carry = sum / 10;
        }
        return result;
    }

    static BigInt absSubtract(BigInt a, BigInt b) 
    {
        if (absLessThan(a, b)) 
        {
            BigInt res = absSubtract(b, a);
            res.isNegative = true;
            return res;
        }

        BigInt result;
        result.digits = "";
        int borrow = 0;

        for (int i = 0; i < a.digits.size(); ++i) 
        {
            int d1 = a.digits[i] - '0';
            int d2 = i < b.digits.size() ? b.digits[i] - '0' : 0;
            int diff = d1 - d2 - borrow;

            if (diff < 0) 
            {
                diff += 10;
                borrow = 1;
            }
            else 
            {
                borrow = 0;
            }
                result.digits += diff + '0';
        }

        result.trim();
        return result;
    }

    static BigInt add(const BigInt& a, const BigInt& b) 
    {
        if (a.isNegative == b.isNegative) 
        {
            BigInt res = absAdd(a, b);
            res.isNegative = a.isNegative;
            return res;
        }
        else 
        {
            BigInt res = absSubtract(a, b);
            res.isNegative = absLessThan(a, b) ? b.isNegative : a.isNegative;
            res.trim();
            return res;
        }
    }

    static BigInt subtract(BigInt a, BigInt b) 
    {
        b.isNegative = !b.isNegative;
        return add(a, b);
    }

    static BigInt multiply(const BigInt& a, const BigInt& b) 
    {
        BigInt result;
        result.digits = string(a.digits.size() + b.digits.size(), '0');
        result.isNegative = (a.isNegative != b.isNegative);

        for (int i = 0; i < a.digits.size(); ++i) 
        {
            int carry = 0;
            int d1 = a.digits[i] - '0';
            for (int j = 0; j < b.digits.size() || carry; ++j) 
            {
                int d2 = j < b.digits.size() ? b.digits[j] - '0' : 0;
                int cur = (result.digits[i + j] - '0') + d1 * d2 + carry;
                result.digits[i + j] = (cur % 10) + '0';
                carry = cur / 10;
            }
        }

        result.trim();
        return result;
    }

    static BigInt divide(BigInt a, BigInt b, bool& errorDivZero) 
    {
        if (b.digits == "0") 
        {
            errorDivZero = true;
            return BigInt("0");
        }

        BigInt result;
        result.digits = "";
        result.isNegative = (a.isNegative != b.isNegative);

        a.isNegative = b.isNegative = false;

        BigInt cur;
        cur.digits = "";

        for (int i = a.digits.size() - 1; i >= 0; --i) 
        {
            cur.digits.insert(cur.digits.begin(), a.digits[i]);
            cur.trim();

            int low = 0, high = 9, mid, x = 0;
            while (low <= high) 
            {
                mid = (low + high) / 2;
                BigInt temp = multiply(b, BigInt(to_string(mid)));
                if (!absLessThan(cur, temp)) 
                {
                    x = mid;
                    low = mid + 1;
                }
                else 
                {
                    high = mid - 1;
                }
            }
            result.digits += (x + '0');
            cur = absSubtract(cur, multiply(b, BigInt(x)));
        }

        reverse(result.digits.begin(), result.digits.end());
        result.trim();
        return result;
    }
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isValidExpression(const string& expr) {
    int balance = 0;
    bool prevIsOperand = false;
    bool prevIsOperator = false;
    bool preIsSpace = false;
    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        
        if (isspace(c)) {
            continue;
            preIsSpace = true;
        }
        if (isdigit(c)) {
            if (prevIsOperand && preIsSpace) return false; 
            prevIsOperand = true;
            prevIsOperator = false;
        }
        else if (c == '(') {
            ++balance;
            prevIsOperand = false;
            prevIsOperator = false;
            preIsSpace = false;
        }
        else if (c == ')') {
            --balance;
            if (balance < 0) return false;
            prevIsOperand = true;
            prevIsOperator = false;
            preIsSpace = false;

        }
        else if (isOperator(c)) {
            if (i == 0 && c != '-') return false; 
            if (prevIsOperator) return false; 
            prevIsOperand = false;
            prevIsOperator = true;
            preIsSpace = false;

        }
        else {
            return false; 
        }
    }

    if (prevIsOperator) return false; 
    return balance == 0; 
}
vector<string> toPostfix(const string& expr, bool& isValid) {
    vector<string> output;
    stack<char> ops;
    size_t i = 0;

    while (i < expr.size()) {
        if (isspace(expr[i])) {
            ++i;
            continue;
        }

        if (isdigit(expr[i])) {
            string num;
            while (i < expr.size() && isdigit(expr[i])) num += expr[i++];
            output.push_back(num);
        }
        else if (expr[i] == '(') {
            ops.push('(');
            ++i;
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            if (ops.empty()) {
                isValid = false;
                return {};
            }
            ops.pop();
            ++i;
        }
        else if (isOperator(expr[i])) {
            string op(1, expr[i]);

            if ((i == 0 || expr[i - 1] == '(') && expr[i] == '-') {
                ++i;
                string num = "-";
                while (i < expr.size() && isdigit(expr[i])) num += expr[i++];
                output.push_back(num);
                continue;
            }

            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push(expr[i]);
            ++i;
        }
        else {
            isValid = false;
            return {};
        }
    }

    while (!ops.empty()) {
        if (ops.top() == '(') {
            isValid = false;
            return {};
        }
        output.push_back(string(1, ops.top()));
        ops.pop();
    }

    return output;
}

BigInt evaluatePostfix(const vector<string>& tokens, bool& errorDivZero) {
    stack<BigInt> st;
    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            st.push(BigInt(token));
        }
        else {
            if (st.size() < 2) return BigInt("0");
            BigInt b = st.top(); st.pop();
            BigInt a = st.top(); st.pop();
            if (token == "+") st.push(BigInt::add(a, b));
            else if (token == "-") st.push(BigInt::subtract(a, b));
            else if (token == "*") st.push(BigInt::multiply(a, b));
            else if (token == "/") st.push(BigInt::divide(a, b, errorDivZero));
        }
    }
    return st.top();
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Nhap theo cu phap: ./24120178 tests.txt output_24120178.txt\n";
        return 1;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    string line;
    while (getline(in, line)) {
        bool isValid = isValidExpression(line);
        bool errorDivZero = false;

        if (!isValid) {
            out << "Error\n";
            cout << "Error\n";
            continue;
        }

        vector<string> postfix = toPostfix(line, isValid);

        if (!isValid) {
            out << "Error\n";
            cout << "Error\n";
            continue;
        }

        BigInt result = evaluatePostfix(postfix, errorDivZero);
        if (errorDivZero) {
            out << "Error\n";
            cout << "Error\n";
        }
        else {
            string res = result.toString();
            out << res << '\n';
            cout << res << '\n';
        }
    }

    in.close();
    out.close();
    return 0;
}