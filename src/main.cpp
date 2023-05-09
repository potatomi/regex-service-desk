#include <bits/stdc++.h>
#include <regex>
using namespace std;

struct Input
{
    string content;
    string code;
};

Input parseInput();
string regexMain();
void testRegex(string s);

int main()
{
    string finalRegex = regexMain();
    cout << "Your final regex is: \\" << finalRegex << "\\ (contents between the back slashes)" << endl;
    testRegex(finalRegex);

    return 0;
}

string regexMain()
{
    string finalRegex = "";
    bool exitFlag = false;
    while (!exitFlag)
    // if this flag is true,
    // it means the user finished creating the regex,
    // and we move on to testing the regex
    {
        cout << "Your current regex is: \\" << finalRegex << "\\" << endl;
        cout << "Enter your next regex pattern, "
             << "it will concatenate to your regex.\n"
             << "enter !finish to end current process, "
             << "enter r(<your_string_here>) to avoid any special commands."
             << endl;
        Input myInput = parseInput();
        if (myInput.code == "finish" || myInput.code == "f")
        {
            exitFlag = true;
            break;
        }
        finalRegex += myInput.content;
    }
    return finalRegex;
}

void testRegex(string pattern)
{
    cout << "You're currently testing: \\" << pattern << "\\" << endl;
    cout << "Enter the string you want to test" << endl;
    cout << "enter !finish to end current process, "
         << "enter r(<your_string_here>) to avoid any special commands." << endl;
    bool exitFlag = false;
    while (!exitFlag)
    {

        Input myInput = parseInput();
        if (myInput.code == "finish" || myInput.code == "f")
        {
            exitFlag = true;
            break;
        }
        if (regex_search(myInput.content, regex(pattern)))
        {
            cout << "Match found for: " << myInput.content << endl;
        }
        else
        {
            cout << "Match not found for: " << myInput.content << endl;
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
