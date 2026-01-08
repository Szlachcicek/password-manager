#include <iostream>
#include "password.hpp"
#include "manager.hpp"
#include <vector>

using std::cout;

int main()
{
    cout << "Test for Password::\n\nClass a" << "\n";
    ks::Password a;
    cout << a;
    
    cout << "\nClass b" << "\n";
    ks::Password b("www.url.pl");
    cout << b;
    
    cout << "\nClass c" << "\n";
    ks::Password c("url", "password");
    cout << c;

    // cout << "\nEncryption test\n";
    // cout << a.encryption() << "\n";

    // cout << "\nEncryption and decryption test\n";
    // c.decryption(a.encryption());
    // cout << a;

    cout << "\nGetter and setter test\n";
    c.setPassword("pass");
    c.setURL("url2");
    cout << c.getCreationTime() << "\n";
    cout << c.getURL() << "\n";
    cout << c.getPassword() << "\n";

    cout << "\nOperator '==' overload  test\n";
    cout << (c==b) << "\n";



    cout << "\nTest for Manager::\n\nClass m1";
    ks::Manager m1;
    cout << m1;

    cout << "\nClass m2\n";

    ks::Manager m2("pass.txt");
    cout << m2;

    cout << "\nSetter and getter test\n";
    m1.setPath("plik2.txt");
    cout << m1.getPath() << "\n";

    cout << "\nExporting test\n";

    std::vector<ks::Password> database;
    database.push_back(c);
    database.push_back(a);
    database.push_back(b);
    
    m2.exporting(database);
    
    cout << "\nImporting test\n";
    
    std::vector<ks::Password> database2;
    database2 = m2.importing();

    cout << database2[0];
    cout << database2[1];
    cout << database2[2];

    return 0;
}