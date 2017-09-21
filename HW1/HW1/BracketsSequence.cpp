#include <iostream>
#include <string>
#include <vector>


char getMatchingOpening(char parenthesis)
{
    if (parenthesis == ')')
        return '(';
    if (parenthesis == ']')
        return '[';
    if (parenthesis == '}')
        return '{';
}


bool isClosing(char parenthesis)
{
    return parenthesis == ')' || parenthesis == ']' || parenthesis == '}';
}


bool isValid(std::string & parentheses, int * lastValidPosition)
{
    int sequenceLength = parentheses.length();
    std::vector<char> stack;

    for (int parenthesisPosition = 0; parenthesisPosition < sequenceLength; ++parenthesisPosition)
    {
        char currentParenthesis = parentheses[parenthesisPosition];
        if (isClosing(currentParenthesis))
        {
            if (stack.back() != getMatchingOpening(currentParenthesis))
            {
                *lastValidPosition = parenthesisPosition;
                return false;
            }
            stack.pop_back();
            continue;
        }
        stack.push_back(currentParenthesis);
    }

    *lastValidPosition = stack.size();
    return 
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string parentheses;
    std::cin >> parentheses;
    
    int lastValidPosition;
    if (isValid(parentheses, &lastValidPosition))
        std::cout << "CORRECT";
    else
        std::cout << lastValidPosition;
}