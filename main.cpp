#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>

using namespace std;

struct Interesting_string
{
    string word;
    size_t length;
    int sum_of_ascii;
    bool primary;
    bool ascending;
    bool repeteable;

    Interesting_string(string s, vector<string> p) :
        word(s),
        length(s.size()),
        sum_of_ascii(0),
        repeteable(check_repeteable(p)),
        ascending(check_ascending())
    {
        for(unsigned int i = 0; i < length; i++)
            sum_of_ascii += (int)s.at(i);

        primary = check_primary();
    }

    bool check_primary()
    {
        for(unsigned int i = 2; i <= (sum_of_ascii/2) ; i++)
        {
            if(sum_of_ascii % i == 0)
                return 0;
        }
        return 1;
    }

    bool check_ascending()
    {
        for (unsigned int i = 0; i < (length - 1) ;)
        {
            if((int)word.at(i) >= (int)word.at(++i))
                return 0;
        }
        return 1;
    }

    bool check_repeteable(vector<string> prev)
    {
        for(unsigned int i = 0; i < prev.size();i++)
        {
            if(word == prev.at(i))
                return 1;
        }
        return 0;
    }
};

int main()
{
    fstream file;
    file.open("NAPIS.txt", ios::in);

    string line;
    vector <string> previous_words;

    int ans_a(0);
    vector<string> ans_b;
    vector<string> ans_c;

    while(getline(file,line))
    {
        Interesting_string current(line, previous_words);

        if(current.primary)
            ans_a++;

        if(current.ascending)
            ans_b.push_back(current.word);

        if(current.repeteable)
            ans_c.push_back(current.word);

        previous_words.push_back(current.word);
    }
    file.close();

    cout << "5.a" << endl << "Napisow pierwszych jest: " << ans_a << endl << endl;
    cout << "5.b" << endl << "Napisy rosnace:" << endl;

    for (string s : ans_b)
        cout << s << endl;

    cout << endl << "5.c" << endl << "Napisy powtarzajace sie: " << endl;

    for (string s : ans_c)
        cout << s << endl;
    return 0;
}
