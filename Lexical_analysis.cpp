#include <iostream>
#include <fstream>
#include <list>
using namespace std;
/*
# Lexical Analysis by Aman Srivastava
# This code differentiates between the keyword, identifier, punctuator and unknown literals 
# Note:: This code is not taking the two character sized operator into consideration while 
   performing Lexical Analysis. Anyhow this that can also be implemented by adding some more functions.
*/
bool check_keyword(string s)
{
    string keyword_list[] = {"asm", "double", "new", "switch",
                             "auto", "else", "operator", "template",
                             "break", "enum", "private", "this",
                             "case", "extern", "protected", "throw",
                             "catch", "float", "public", "try",
                             "char", "for", "register", "typedef",
                             "class", "friend", "return", "union",
                             "const", "goto", "short", "unsigned",
                             "continue", "if", "signed", "virtual",
                             "default", "inline", "sizeof", "void",
                             "delete", "int", "static", "volatile",
                             "do", "long", "struct", "while"};
    for (auto x : keyword_list)
    {
        if (s == x)
            return true;
    }
    return false;
}
bool check_punctuator(char ch)
{
    char c[] = {'#', '*', ',', ';', '(', ')', '{', '}', '[', ']', '<', '>'};
    for (auto x : c)
    {
        if (ch == x)
            return true;
    }
    return false;
}

bool check_space(char c)
{
    char *ch;
    *ch = c;
    return ch == " ";
}

bool check_operator(char ch)
{

    char c[] = {'+', '-', '&', '|', '/', '*', '%', '^', '='};
    for (auto x : c)
    {
        if (ch == x)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    ifstream file;

    // file.open(*(argv + 1));   // Uncommented this line if you want to give any command line argument and comment the below line
    file.open("Filename.txt");   // Enter the filename on which you want to do the lexical analysis 

    char c;
    int count_keyword = 0;
    int count_identifier = 0;
    int count_punctuator = 0;
    int count_unknown = 0;
    list<string> keyword_list;
    list<string> identifier_list;
    list<string> punctuator_list;
    list<string> unknown_list;
    string s;
    s = "";
    string us = "";
    int flag = 0;
    // You can uncommented the line in the while loop if you want to track whenever a token is found
    while (!file.eof())
    {
        c = file.get();
        if (c == 34 || flag == 1)
        {
            us = us + c;
            if (flag == 0)
            {
                flag = 1;
                count_unknown++;
            }
            else if (c == 34 && flag == 1)
            {
                // cout << "Unknown found:"<<us << endl;
                flag = 0;
                unknown_list.push_back(us);
            }
            continue;
        }
        if (c == ' ' || c == '\n')
        {
            if (s != "")
            {
                if (check_keyword(s))
                {
                    // cout << "Keyword found:"<<s<<endl;
                    keyword_list.push_back(s);
                    count_keyword++;
                    s = "";
                }
                else
                {
                    // cout<<"Identifier found:"<<s<<endl;
                    identifier_list.push_back(s);
                    count_identifier++;
                    s = "";
                }
            }
        }
        else if (check_punctuator(c))
        {
            // cout <<"Punctuator found:"<< c << endl;
            string cs = "";
            cs = cs + c;
            punctuator_list.push_back(cs);
            count_punctuator++;
            if (s != "")
            {
                if (check_keyword(s))
                {
                    // cout << "Keyword found:"<<s;
                    keyword_list.push_back(s);
                    count_keyword++;
                    s = "";
                }
                else
                {
                    // cout<<"Identifier found:"<<s<<endl;
                    identifier_list.push_back(s);
                    count_identifier++;
                    s = "";
                }
            }
        }
        else
        {
            s += c;
        }
        if (check_keyword(s))
        {
            // cout<<"Keyword found:"<<s<<endl;
            keyword_list.push_back(s);

            count_keyword++;
            s = "";
        }
    }
    cout << endl;

    cout << "Count of keyword:" << count_keyword << endl;
    cout << "List of keyword found->" << endl;
    for (auto x : keyword_list)
    {
        cout << x << "    ";
    }
    cout << endl
         << endl;

    cout << "Count of Identifier:" << count_identifier << endl;
    cout << "List of Identifier found->" << endl;
    for (auto x : identifier_list)
    {
        cout << x << "    ";
    }
    cout << endl
         << endl;

    cout << "Count of Punctuators:" << count_punctuator << endl;
    cout << "List of Punctuators found->" << endl;
    for (auto x : punctuator_list)
    {
        cout << x << "    ";
    }
    cout << endl
         << endl;

    cout << "Count of Unknown:" << count_unknown << endl;
    cout << "List of Unknown found->" << endl;
    for (auto x : unknown_list)
    {
        cout << x << "    ";
    }
    cout << endl
         << endl;

    return 0;
}
// Lexical Analysis by Aman Srivastava
