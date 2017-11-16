#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "mylib.h"
using namespace KennethLo;

void color_ch(char ch, int color_code)
{
    cout << "\e[" << color_code << "m" << ch << "\e[0m";
}

class StringMatching {
public:
    StringMatching() {}
    virtual ~StringMatching() {}

    virtual void reset(void) = 0;

    virtual void prepare(const vector<string>& patterns) = 0;

    virtual void process(const string& text) = 0;

    virtual string getResult() = 0;
};

class StringMatching_MP : public StringMatching
{
public:
    StringMatching_MP() {}
    virtual ~StringMatching_MP() {}

    virtual void reset(void)
    {
        m_table.clear();
        m_table_mine.clear();
        m_found.clear();
        m_text = "";
        m_pattern = "";
    }

    virtual void prepare(const vector<string>& patterns)
    {
        m_pattern = patterns[0];
        m_prepare_mine(m_pattern);
        m_prepare(m_pattern);
    }

    virtual void process(const string& text)
    {
        m_text = text;
        int posT = 0, posP = 0;
    
        cout << text << endl;
        while (posT < text.size())
        {
            if (text[posT] == m_pattern[posP])
            {
                color_ch(m_pattern[posP], 32);
                if (++posP == m_pattern.size())
                {
                    m_found.push_back(posT - m_pattern.size() + 1);
                    posP = m_table[posP];

                    cout << endl << string(posT + 1 - posP, ' ');
                    if (posP > 0)
                    {
                        cout << m_pattern.substr(0, posP);    
                    }
                }
                ++posT;
            }
            else
            {
                color_ch(m_pattern[posP], 31);
                
                posP = m_table[posP];
                
                if (posT < text.size())
                {
                    cout << endl << string(posT - posP, ' ');
                    if (posP > 0)
                    {
                        cout << m_pattern.substr(0, posP);    
                    }
                }
            }
            if (posP < 0)
            {
                ++posP;
                ++posT;
            }
        }
        cout << endl;
    }

    virtual string getResult()
    {
        string result = "";
        if (m_found.size() == 0)
        {
            result = "Not found.";
        }
        else
        {
            cout << m_found << endl;
    
            size_t j = 0;
            int escaping = 0;
            for (size_t i = 0; i < m_text.size(); i++)
            {
                if (m_found[j] == i)
                {
                    escaping = m_pattern.size();
                    result += "\e[31m";
                    j++;
                }
                result += m_text[i];
                if (escaping && --escaping == 0)
                {
                    result += "\e[0m";
                }
            }
        }    
        return result;
    }

private:
    vector<int> m_table;
    vector<int> m_table_mine;
    string m_text;
    string m_pattern;
    vector<int> m_found;

    void m_prepare_mine(const string& str)
    {
        m_table_mine.resize(str.size() + 1, -1);
        
        for (size_t i = 1; i < str.size(); i++)
        {
            if (str[i] == str[m_table_mine[i-1]])
            {
                m_table_mine[i] = m_table_mine[i-1] + 1;
            }
        }
    
    }

    void m_prepare(const string& str)
    {
        m_table.resize(str.size() + 1, -1);
    
        int i = 0;
        int j = m_table[0];
        while (i < str.size())
        {
            while (j > -1 && str[i] != str[j])
            {
                j = m_table[j];
            }
            m_table[++i] = ++j;
        }
    }
};

int main(void) 
{
    int q, n;
    string line;
    getline(cin, line);
    q = stoi(line);

    StringMatching* m = new StringMatching_MP();
    for (int i = 0; i < q; i++)
    {
        getline(cin, line);
        n = stoi(line);

        vector<string> patterns(n);
        for (int j = 0; j < n; j++)
        {
            getline(cin, patterns[j]);
        }
        string text, pattern;
        getline(cin, text);

        m->reset();
        m->prepare(patterns);
        m->process(text);
        cout << m->getResult() << endl;
    }

    return 0;
}

