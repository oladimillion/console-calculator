#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <cmath>

using std::cout;
using std::cerr;
using std::endl;

#define PI 3.14159265
#define MAX_SIZE 101

void eatspaces(char * str);
double calculate(char * str);
double term(char * str, size_t &index);
double number(char * str, size_t &index);
char* extract(char * str, size_t &index);
size_t numofbrackets(char * str);
void fixbrackets(char *str);
double calculate_bracket_expression(char *str);
void clearall(char *str, int size);
void do_calculations(char *str);
void math_functions(char *accum, size_t &index, double (*do_math)(double), double (*DRG)(double));
void call_math_function(char *accum, size_t index);
double to_degrees(double);
double normal(double);
double  sq(double);
void init_calculator(char *cstr);
void my_merge(char *accum, const char *result, size_t L, size_t R);
void validate(char *str);
double pn_value(double value, bool negative_value);





int main()
{
    //char cstr[] = "3.5(1.25-3/(1.333-2.1*1.6))-1";
    //char cstr[] = "8(2+8(9-8))*8(2+8)*8(2+8)";
    //char cstr[] = "(6/2)*(1+2)";
    //char cstr[] = "(6/2)*(1+2(9+(9+8)))";
    char cstr[] = "(((2++0+9))*(9 + 5))";
    //char cstr[] = "(-2 * log(8))";

    cout << "YOU ENTERED : "<< cstr << endl << endl;
    init_calculator(cstr);


    return 0;
}

void init_calculator(char *cstr)
{
    char *accum = new char[MAX_SIZE];
    clearall(accum, MAX_SIZE);
    strcpy(accum, cstr);

    try
    {
        eatspaces(accum);
        fixbrackets(accum);
        validate(accum);
        do_calculations(accum);

        cout << endl;
        cout << "RESULT: " << accum << endl;
    }
    catch(char* error)
    {
        cerr << endl;
        cerr << "ERROR: " << error << endl;
        delete [] error;
    }
    delete [] accum;
}

void eatspaces(char * str)
{
    size_t i = 0;
    size_t j = 0;

    while((*(str + i) = *(str + j++) ) != '\0')
    {
        if(*(str + i) != ' ')
        {
            i++;
        }
    }
}

void fixbrackets(char *str)
{
    size_t i = 0;
    size_t j = 0;

    char fixedstr [MAX_SIZE];
    clearall(fixedstr, MAX_SIZE);


    strcpy(fixedstr, str);

    while(*(str + i))
    {
        if(isdigit(*(str + i)) && *(str + i + 1) == '(')
        {
            i++;
            *(fixedstr + ++j) = '*';
            strncpy((fixedstr + ++j), (str  + i), strlen(str) - i);
        }
        j++;
        i++;
    }

    clearall(str, MAX_SIZE);

    cout << "fixedstr" << fixedstr << endl;
    strcpy(str, fixedstr);
}


double sq(double data)
{
    return data * data;
}

double normal(double data)
{
    return data;
}

void validate(char *str)
{
    char *error = new char[50];
    size_t index = 0;

    while(*(str + index))
    {
        if(*(str + index) == '(' && *(str + index + 1) == ')' )
        {
            char err[40];
            strcpy(err, "invalid input at: ");
            strcat(err, str + index);
            strcpy(error, err);

            throw error;
        }

        index++;
    }

    index = 0;

    size_t L = 0;
    size_t R = 0;

    while(*(str + index))
    {
        switch(*(str + index))
        {
            case '(':
                L++;
                break;
            case ')':
                R++;
                break;
        }

        index++;
    }
    index = 0;

    if(L != R)
    {
        strcpy(error, "Some brackets missing");
        throw error;
    }
}


size_t numofbrackets(char * str)
{
    size_t i = 0;
    size_t j = 0;

    while(*(str + i))
    {
        if(isdigit(*(str + i)) && *(str + i + 1) == '(')
            j++;
        i++;
    }
    return j;
}

void clearall(char *str, int size)
{
    memset(str, '\0', size);
}


char *extract_expression(char *str, size_t &index)
{
    size_t L = 0;

    while(*(str + index))
    {
        if(*(str + index) == '(')
        {
            L = index;
        }
        else if(*(str + index) == ')')
        {
            break;
        }

        index++;
    }

    size_t SIZE = index - L;
    char *temp = new char[SIZE];

    clearall(temp, SIZE);
    strncpy(temp, str + L + 1, SIZE - 1);

    return temp;
}

void my_merge(char *accum, const char *result, size_t L, size_t R)
{
    char lData[L + 1];
    char rData[strlen(accum) - R + 1];

    clearall(lData, L + 1);
    clearall(rData, strlen(accum) - R + 1);

    strncpy(lData, accum, L);
    strncpy(rData, accum + R + 1, strlen(accum) - R + 1);

    cout << "lData: " << lData << endl;
    cout << "rData: " << rData << endl;

    clearall(accum, MAX_SIZE);

    strcat(accum, lData);
    strcat(accum, result);
    strcat(accum, rData);
}

void math_functions(char *accum, size_t &index, double (*do_math)(double), double (*DRG)(double))
{
    size_t L = index;
    char *temp = extract_expression(accum, index);
    size_t R = index;

    double value = do_math(DRG(calculate_bracket_expression(temp)));
    const char *result = std::to_string(value).c_str();

    my_merge(accum, result, L, R);

    delete [] temp;
}

void call_math_function(char *accum, size_t index)
{
    if(strncmp(accum + index, "sin", 3) == 0)
    {
        math_functions(accum, index, sin, to_degrees);
    }
    else if(strncmp(accum + index, "cos", 3) == 0)
    {
        math_functions(accum, index, cos, to_degrees);
    }
    else if(strncmp(accum + index, "tan", 3) == 0)
    {
        math_functions(accum, index, tan, to_degrees);
    }
    else if(strncmp(accum + index, "asin", 4) == 0)
    {
        math_functions(accum, index, asin, to_degrees);
    }
    else if(strncmp(accum + index, "acos", 4) == 0)
    {
        math_functions(accum, index, acos, to_degrees);
    }
    else if(strncmp(accum + index, "atan", 4) == 0)
    {
        math_functions(accum, index, atan, to_degrees);
    }
    else if(strncmp(accum + index, "sqrt", 4) == 0)
    {
        math_functions(accum, index, sqrt, normal);
    }
    else if(strncmp(accum + index, "sq", 2) == 0)
    {
        math_functions(accum, index, sq, normal);
    }
    else if(strncmp(accum + index, "log10", 3) == 0)
    {
        math_functions(accum, index, log10, normal);
    }
}

void do_calculations(char *accum)
{
    bool again = false;
    size_t count = 0;

    do
    {
        size_t index = 0;
        again = false;
        size_t pos = 0;

        while(*(accum + index))
        {
            if(strncmp(accum + index, "sin", 3) == 0)
            {
                again = true;
                pos = index;
                index += 3;
            }
            else if(strncmp(accum + index, "cos", 3) == 0)
            {
                again = true;
                pos = index;
                index += 3;
            }
            else if(strncmp(accum + index, "tan", 3) == 0)
            {
                again = true;
                pos = index;
                index += 3;
            }
            else if(strncmp(accum + index, "asin", 4) == 0)
            {
                again = true;
                pos = index;
                index += 4;
            }
            else if(strncmp(accum + index, "acos", 4) == 0)
            {
                again = true;
                pos = index;
                index += 4;
            }
            else if(strncmp(accum + index, "atan", 4) == 0)
            {
                again = true;
                pos = index;
                index += 4;
            }
            else if(strncmp(accum + index, "sqrt", 4) == 0)
            {
                again = true;
                pos = index;
                index += 4;
            }
            else if(strncmp(accum + index, "sq", 2) == 0)
            {
                again = true;
                pos = index;
                index += 2;
            }
            else if(strncmp(accum + index, "log", 3) == 0)
            {
                again = true;
                pos = index;
                index += 3;
            }
            index++;
        }

        if(again)
        {
            call_math_function(accum, pos);
        }
        else
        {
            double value = calculate_bracket_expression(accum);
            const char *result = std::to_string(value).c_str();

            clearall(accum, strlen(accum));
            strcpy(accum, result);
        }

    }
    while(again);
}


double calculate_bracket_expression(char *accum)
{
    bool again = false;
    int count = 0;
    double final_result = 0;

    do
    {
        size_t index = 0;
        size_t L = 0;
        size_t R = 0;
        again = false;

        cout << "count: " << count << endl;

        while(*(accum + index))
        {
            if(*(accum + index) == '(' && !isalpha(*(accum + index - 1)))
                L = index;
            else if(*(accum + index) == ')')
            {
                R = index;
                again = true;
                break;
            }
            index++;
        }

        index = L;

        if(again)
        {
            char *temp = extract_expression(accum, index);
            final_result = calculate(temp);
            const char *result = std::to_string(final_result).c_str();

            my_merge(accum, result, L, R);

            delete [] temp;
        }
        else
        {
            final_result = calculate(accum);

            const char *result = std::to_string(final_result).c_str();

            clearall(accum, strlen(accum));
            strcpy(accum, result);
        }
        cout << " end: " << accum << endl;
        count++;
    }
    while(again);

    return final_result;
}

double calculate(char * str)
{
    double value = 0;
    size_t index = 0;
    value = term(str, index);
    while(true)
    {
        switch(*(str + index++))
        {
            case '\0':
                return value;
            case '+':
                value += term(str, index);
                break;
            case '-':
                value -= term(str, index);
                break;
            default:
                char *error = new char[200];
                strcpy(error, "Expression evaluation error. Found: ");
                strncat(error, str + index - 1, 2);
                throw error;
                break;
        }
    }
}

double pn_value(double value, bool negative_value)
{
    if(negative_value)
        value = 0 - value;

    return value;
}

double number(char * str, size_t &index)
{
    double value = 0;
    bool negative_value = false;

    if(*(str + index) == '-')
    {
        negative_value = true;
        index++;
    }
    else if(*(str + index) == '+')
    {
        index++;
    }

    if(!isdigit(*(str + index)))
    {
        char *error = new char[100];

        clearall(error, 100);
        strcat(error, "Invalid character(s) in: ");
        strcat(error, str);

        throw error;
    }

    while(isdigit(*(str + index)))
    {
        value = (value * 10) + (*(str + index++)) - '0';
    }

    if(*(str + index) != '.')
    {
        return pn_value(value, negative_value);
    }

    double factor = 1.0;

    while(isdigit(*(str + ++index)))
    {
        factor *= 0.1;
        value += factor * ((*(str + index)) - '0');
    }

    return pn_value(value, negative_value);
}

double term(char * str, size_t &index)
{
    double value = number(str, index);

    while(true)
    {
        if(*(str + index) == '*')
            value *= number(str, ++index);
        else if(*(str + index) == '/')
            value /= number(str, ++index);
        else
            break;
    }
    return value;
}

double to_degrees(double data)
{
    return (data * PI / 180);
}
