#include <bits/stdc++.h>
#include <regex>
using namespace std;

struct Input
{
    string content;
    string code;
};

void regexMain();
string makeRegex();
void testRegex(string s);

Input parseInput();
void printQuitInstructions();
string autoEscape(const string &s);

string promptLiteral();
string promptSet();
string promptRange();
string promptSpecial();

int main()
{
    // regexMain();

    // test code goes here.

    return 0;
}

void regexMain()
{
    string finalRegex = makeRegex();
    cout << "Your final regex is: \\" << finalRegex << "\\ (contents between the back slashes)" << endl;
    testRegex(finalRegex);
}

string makeRegex()
{
    string finalRegex = "(";
    bool exitCurrentProcess = false;
    // for user inputs
    int intInput;
    char charInput;
    string newPattern;
    while (!exitCurrentProcess)
    {
        cout << "Your current regex is: \\" << finalRegex << "\\" << endl;

        // TODO: prompt user to...
        // enter what type of input
        // literal/range/special
        cout << "What type of string do you want next? "
             << "\n\t1 - exact string(literal);\n\t2 - match one of the chars;\n\t3 - match a range of chars; \n\t4 - special;"
             << endl;
        cin >> intInput;

        // support for () groups will be added later
        // probably with recursion

        // TODO: switch statements
        switch (intInput)
        {
        case 1:
            newPattern = promptLiteral();
            break;
        case 2:
            newPattern = promptRange();
            break;
        case 3:
            newPattern = promptRange();
            break;
        case 4:
            newPattern = promptSpecial();
            break;
        default:
            continue;
        }
        finalRegex += newPattern;

        // TODO: prompt a detailed question
        // TODO: prompt for repititions

        // TODO: ask user if an "or" is needed in this sequence
        // if yes, add | to the regex
        // if not, add ) to the regex,
        // and ask if anything else should be concatenated after
        // if yes, add (
        // if not, exit flag = true
    }
    return finalRegex;
}

void testRegex(string pattern)
{
    cout << "You're currently testing: \\" << pattern << "\\" << endl;
    cout << "Enter the string you want to test" << endl;
    printQuitInstructions();
    bool exitCurrentProcess = false;
    while (!exitCurrentProcess)
    {

        Input myInput = parseInput();
        if (myInput.code == "finish" || myInput.code == "f")
        {
            exitCurrentProcess = true;
            break;
        }
        if (regex_search(myInput.content, regex(pattern)))
        {
            cout << "Match found for: \"" << myInput.content << "\"" << endl;
        }
        else
        {
            cout << "Match not found for: \"" << myInput.content << "\"" << endl;
        }
    }
}

Input parseInput()
{
    string inputLine = "";
    getline(cin, inputLine);
    if (inputLine[0] == '!')
    {
        return {"", inputLine.substr(1)};
    }
    if (inputLine.substr(0, 2) == "r(" && inputLine.back() == ')')
    {
        inputLine.erase(inputLine.size() - 1);
        inputLine.erase(0, 2);
    }
    return {inputLine, ""};
}

void printQuitInstructions()
{
    cout << "enter !finish or !f to end current process, "
         //  << "enter !help or !h to show help menu, "
         << "enter r(<your_string_here>) to avoid any special commands." << endl;
}

string autoEscape(const string &s)
{
    string escaped = "";
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        switch (*it)
        {
        case '\\':
        case '^':
        case '$':
        case '.':
        case '|':
        case '?':
        case '*':
        case '+':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case ' ':
            escaped += '\\';
            // Fall through to default case
        default:
            escaped += *it;
            break;
        }
    }
    return escaped;
}

string promptLiteral()
{
    cout << "enter the exact string that you want to match\n"
         << "don't worry about escape characters - They'll be parsed automatically\n";
    string inputLine = "";
    getline(cin, inputLine);
    inputLine = autoEscape(inputLine);
    return inputLine;
}

string promptSet()
{
}
string promptRange()
{
}
string promptSpecial()
{
}