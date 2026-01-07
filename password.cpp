#include "password.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    Password::Password()
    {
        time(&m_creationDate);
    }
    
    Password::Password(const std::string& url):m_url(url)
    {
        srand(static_cast<unsigned int>(time(0)));
        for(int i=0; i<15; i++)
        {
            int random = rand() % 92+33;
            m_password += random;
        }
        time(&m_creationDate);
    }
    
    Password::Password(const std::string& password, const std::string& url):m_password(password), m_url(url)
    {
        time(&m_creationDate);
    }
    
    std::string Password::encryption() const
    {
        std::string pass;
        for(int i = 0; i<m_password.length(); i++)
        { 
        pass[i]=m_password[i]+5;
    
            if(pass[i]>125)
            {
                int j = pass[i]-126;
                pass[i]=33+j;
            }
       }
    
        return std::to_string(m_id) + "|" + pass + "|" + m_url + "|" + std::to_string(m_creationDate);
    }
    
    void Password::decryption(const std::string& data)
    {
        std::stringstream line(data);
        std::string segment;

        if(std::getline(line, segment, '|'))
        {
            m_id = std::stoi(segment);
        }

        if(std::getline(line, segment, '|'))
        {
            for(int i = 0; i<m_password.length(); i++)
            {
                segment[i]=m_password[i]-5;
                
                if(segment[i]<33)
                {
                    int j = segment[i]-32;
                    segment[i]=125+j;
                }
            }
            
            m_password = segment;
        }
        
        if(std::getline(line, segment, '|'))
        {
            m_url = segment;
        }
        
        if(std::getline(line, segment, '|'))
        {
            long t = std::stol(segment);
            m_creationDate = static_cast<std::time_t>(t);
        }
    }
    
    bool Password::operator==(const Password& other) const
    {
        if(m_password==other.m_password && m_url==other.m_url)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    std::ostream& operator<<(std::ostream& os, const Password& p)
    {
        os << p.m_password << "\n" << p.m_url << "\n" << p.m_creationDate << "\n";
    
        return os;
    }
    
    void Password::setPassword(const std::string& password)
    {
        if(password.length()>8)
        {
            bool dig{},pct{};
            for(char i : password)
            {
                if(std::isdigit(i))
                {
                    dig = true;
                }
                if(std::ispunct(i))
                {
                    pct = true;
                }
                if(pct==true && dig==true)
                {
                    m_password=password;
                    break;
                }
                else
                {
                    throw std::invalid_argument("Password must contain at leats one special character AND number");
                }
            }
        }
        else
        {
            throw std::invalid_argument("Password must be at least 8 characters long");
        }
    }
    
    void Password::setURL(const std::string& url)
    {
        m_url=url;
    }
    
    std::string Password::getPassword() const
    {
        return m_password;
    }
    
    std::string Password::getURL() const
    {
        return m_url;
    }
    
    std::time_t Password::getCreationTime() const
    {
        return m_creationDate;
    }
}