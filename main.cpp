#include <iostream>
#include "password.hpp"
#include "manager.hpp"
#include "passwordBA.hpp"
#include "passwordCM.hpp"
#include <vector>

using std::cout;

int main()
{
    cout << "Test for Password::\nClass a" << "\n";
    ks::Password a;
    cout << a;
    
    cout << "-------------------------------------------------------------------------\nClass b" << "\n";
    ks::Password b("www.url.pl");
    cout << b;
    
    cout << "-------------------------------------------------------------------------\nClass c" << "\n";
    ks::Password c("url", "password");
    cout << c;

    // cout << "\nEncryption test\n";
    // cout << a.encryption() << "\n";

    // cout << "\nEncryption and decryption test\n";
    // c.decryption(a.encryption());
    // cout << a;

    cout << "-------------------------------------------------------------------------\nGetter and setter test\n\n";
    c.setPassword("pass");
    c.setURL("url2");
    cout << c.getCreationTime() << "\n";
    cout << c.getURL() << "\n";
    cout << c.getPassword() << "\n";

    cout << "-------------------------------------------------------------------------\nOperator '==' overload  test\n";
    cout << (c==b) << "\n";



    cout << "-------------------------------------------------------------------------\nTest for Manager::\n\nClass m1";
    ks::Manager m1;
    cout << m1;

    cout << "-------------------------------------------------------------------------\nClass m2\n";

    ks::Manager m2("pass.txt");
    cout << m2;

    cout << "-------------------------------------------------------------------------\nSetter and getter test\n";
    m1.setPath("plik2.txt");
    cout << m1.getPath() << "\n";

    cout << "-------------------------------------------------------------------------\nExporting test\n";

    std::vector<ks::Password> database;
    database.push_back(c);
    database.push_back(a);
    database.push_back(b);
    
    m2.exporting(database);
    
    cout << "-------------------------------------------------------------------------\nImporting test\n";
    
    std::vector<ks::Password> database2;
    database2 = m2.importing<ks::Password>();
    
    cout << database2[0];
    cout << database2[1];
    cout << database2[2];
    
    cout << "-------------------------------------------------------------------------\nPasswordBA test\n\nClass ba1\n";
    
    ks::PasswordBA ba1;
    cout << ba1;
    cout << "-------------------------------------------------------------------------\nSetter test\n";
    ba1.setClientNumber(111);
    cout << ba1;
    
    cout << "-------------------------------------------------------------------------\nClass ba2\n";
    
    ks::PasswordBA ba2("link", 1234);
    cout << ba2;
    
    cout << "-------------------------------------------------------------------------\nClass ba3\n";
    
    ks::PasswordBA ba3("link2", 123, "not a pass");
    cout << ba3;
    
    cout << "-------------------------------------------------------------------------\nPasswordCM test\n\nClass cm1\n";
    
    ks::PasswordCM cm1;
    cout << cm1;
    cout << "-------------------------------------------------------------------------\nSetter test\n";
    cm1.setLogin("login@me.dot");
    cout << cm1;
    
    cout << "-------------------------------------------------------------------------\nClass cm2\n";
    
    ks::PasswordCM cm2("lru", "mylogin123");
    cout << cm2;
    
    cout << "-------------------------------------------------------------------------\nClass cm3\n";
    
    ks::PasswordCM cm3("lru2", "mylogin2", "mypass");
    cout << cm3;
    
    cout << "---------------------------------------------------------------------\nExporting and importing cm3 test\n";
    
    ks::Manager m3("file.txt");
    std::vector<ks::PasswordCM> database3;
    std::vector<ks::PasswordCM> database4;
    
    database3.push_back(cm1);
    database3.push_back(cm3);
    database3.push_back(cm2);
    
    m3.exporting(database3);
    
    database4 = m3.importing<ks::PasswordCM>();

    cout << database4[0];
    cout << database4[1];
    cout << database4[2];

    return 0;
}