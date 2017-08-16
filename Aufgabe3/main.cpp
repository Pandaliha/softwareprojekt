
#include <iostream>
using namespace std;

class String
{

private:
    int size;
    char* str;


    template <class T>
    void copy(T &source, char* dest, int count, int offset)
    {
        int i;
        for (i = 0; i < count; i++)
        {
            dest[i + offset] = source[i];
        }
        dest[count] = '\0';
    }

public:
    //Standardkonstruktor
    String()
    {
        size = 0;
        str = new char[1];
        str[0] = '\0';
    }

    //Konstruktor Character
    String(char c)
    {
        size = 1;
        str = new char[2];
        str[0] = c;
        str[size] = '\0';
    }

    //Konstruktor C-String
    String(char* c)
    {
        int counter = 0;
        while (c[counter] != '\0')
        {
            counter++;
        }
        str = new char[counter + 1];
        size = counter;
        copy(c, str, size, 0);
    }

    //Kopierkonstruktor
    String(String &s)
    {
        size = s.getSize();
        str = new char[size + 1];
        copy(s, str, size, 0);
    }

    //Getter
    int getSize()
    {
        return size;
    }

    //Dekonstruktor
    ~String()
    {
        delete[] str;
    }

    //Overload Arrayzugriff
    char& operator [](int index)
    {
        return str[index];
    }

    //Overload +=
    String& operator +=(String &s)
    {
        int newsize = size + s.getSize();
        char* newstr = new char[newsize + 1];

        copy(str, newstr, size, 0);
        copy(s, newstr, newsize, size);

        size = newsize;

        delete[] str;
        str = newstr;

        return *this;
    }

    //Overload =
    String& operator =(String &s)
    {
        char* newstr = new char[s.getSize() + 1];
        delete[] str;
        this->str = newstr;
        size = s.getSize();
        copy(s, str, size, 0);

        return *this;
    }

    // make friend, so we can access private members
    friend ostream& operator <<(ostream &out, String &s);
};



ostream& operator<< (ostream &out, String &s)
{
    for(int i = 0; i < s.size; i++)
    {
        out << s.str[i];
    }
    return out;
}

int main(int argc, const char * argv[])
{
    //Todo: Tests
    String s0('c');
    String s1;
    String s2;
    String s3("Hallo");
    String s4 ("34543254 ##");
    String s5 ("        ");
    String s6;
    s1 = s2 = s3;
    s2 += s2;
    s5 += s0;
    s6 += s5;
    cout << s0 << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s3[3] << endl;
    cout << s4 << endl;
    cout << s4[-1] << endl;
    cout << s5 << endl;
    cout << s6 << endl;

}
