#include <bits/stdc++.h>
#include <regex>
using namespace std;
string regexMain();

int main()
{
    string finalRegex = regexMain();
    cout << "Your final regex is: \\" + finalRegex + "\\" << endl;
    return 0;
}

string regexMain()
{
    string finalRegex = "";
    bool exitFlag = false;
    string inputLine;
    while (!exitFlag)
    // if this flag is true,
    // it means the user finished creating the regex,
    // and we move on to testing the regex
    {
        cout << "Your current regex is: \\" + finalRegex + "\\" << endl;
        cout << "Enter your next regex pattern, "
        "it will concatenate to your regex.\n"
        "enter !finish to finish creating and start testing, "
        "enter r(<your_string_here>) to avoid any special commands."
             << endl;
        getline(cin, inputLine);
        if (inputLine == "!finish")
        {
            exitFlag = true;
            break;
        }
        if (inputLine.substr(0, 2) == "r(" && inputLine.back() == ')')
        {
            inputLine.erase(inputLine.size() - 1);
            inputLine.erase(0, 2);
        }
        finalRegex += inputLine;

        /* code */
    }
    return finalRegex;
}
