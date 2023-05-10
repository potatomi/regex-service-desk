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
    regexMain();

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
    int intInput, intInput1, intInput2;
    char charInput;
    string newPattern;
    while (!exitCurrentProcess)
    {
        cout << "Your current regex is: \\" << finalRegex << "\\" << endl;

        cout << "What type of string do you want next? "
             << "\n\t1 - exact string(literal);\n\t2 - match one of the chars;\n\t3 - match a range of chars; \n\t4 - special(or raw regex);"
             << endl;
        cin >> intInput;
        cin.ignore();

        // support for () groups will be added later
        // probably with recursion

        switch (intInput)
        {
        case 1:
            newPattern = promptLiteral();
            break;
        case 2:
            newPattern = promptSet();
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

        // TODO: prompt for repititions
        cout << "Okay, you just added \\" << newPattern << "\\ to your regex\n"
             << "How many times do you want it to repeat?\n"
             << "\n\t1 - once;\n\t2 - a specific number of times;\n\t3 - a range of numbers; \n\t4 - at least n, but up to infinity;"
             << endl;
        cin >> intInput;
        newPattern = "";

        switch (intInput)
        {
        case 1:
            break;
        case 2:
            cout << "enter how many times you want to repeat:\n"
                 << endl;
            cin >> intInput1;
            newPattern = "{" + to_string(intInput1) + "}";
            break;
        case 3:
            cout << "enter how many times you want to repeat, separated by spaces:\n"
                 << endl;
            cin >> intInput1 >> intInput2;
            newPattern = "{" + to_string(intInput1) + "," + to_string(intInput2) + "}";
            break;
        case 4:
            cout << "enter how many times you want to repeat (at least):\n"
                 << endl;
            cin >> intInput1;
            newPattern = "{" + to_string(intInput1) + ",}";
            break;
        default:
            cout << "Hmm, I'm not sure if you entered something legit...\n"
                 << "I'll default to the pattern occuring only once.\n";
        }
        finalRegex += newPattern;

        // TODO: ask user if an "or" is needed in this sequence
        // if yes, add | to the regex
        // if not, add ) to the regex,
        // and ask if anything else should be concatenated after
        // if yes, add (
        // if not, exit flag = true
        cout << "do you want an \'or\' in this sequence? (y/n)" << endl;
        cin >> charInput;
        switch (charInput)
        {
        case 'y':
            finalRegex += "|";
            continue;

        default:
            finalRegex += ")";
            break;
        }
        cout << "do you want to concatenate something new? \nAnswering no would end regex creation. (y/n)" << endl;
        cin >> charInput;
        switch (charInput)
        {
        case 'y':
            finalRegex += "(";
            break;

        default:
            exitCurrentProcess = true;
        }
    }
    return finalRegex;
}

void testRegex(string pattern)
{
    cin.ignore();
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
    cout << "enter the characters that you want to match, case sensitive\n"
         << "don't add spaces in between - spaces are characters as well!\n";
    string inputLine = "";
    getline(cin, inputLine);
    inputLine = autoEscape(inputLine);
    return "[" + inputLine + "]";
}
string promptRange()
{
    cout << "enter the range of characters you want, separated by spaces\n";
    char c1, c2;
    cin >> c1 >> c2;
    cin.ignore();
    if (c1 - c2 > 0)
    {
        cout << "Larger char detected in 1st input - reversing...";
        return "[" + to_string(c2) + "-" + to_string(c1) + "]";
    }
    return "[" + to_string(c1) + "-" + to_string(c2) + "]";
}
string promptSpecial()
{
    cout << "enter whatever regex you want\n"
         << R"(special characters won't be escaped, so you can input stuff like \n, \t for newlines and tabs)"
         << endl;
    string inputLine = "";
    getline(cin, inputLine);
    return inputLine;
}