#include <iostream>
#include "password.hpp"
#include "manager.hpp"

using std::cout;

int main()
{
    cout << "class a" << "\n";
    ks::Password a;
    
    cout << a.getCreationTime() << "\n";
    
    cout << "class b" << "\n";
    ks::Password b("www.url.pl");
    
    cout << b.getCreationTime() << "\n";
    cout << b.getURL() << "\n";
    cout << b.getPassword() << "\n";
    
    cout << "class c" << "\n";
    ks::Password c("url", "password");    

    cout << c.getCreationTime() << "\n";
    cout << c.getURL() << "\n";
    cout << c.getPassword() << "\n";
    cout << c.encryption() << "\n";
    c.decryption(c.encryption());
    cout << "data after encryption and decryption\n";
    cout << c.getCreationTime() << "\n";
    cout << c.getURL() << "\n";
    cout << c.getPassword() << "\n";
    cout << (c==b) << "\n";
    c.setPassword("pass");
    c.setURL("url2");
    cout << c;


    return 0;
}