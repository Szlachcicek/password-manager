#include "password.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    unsigned int Password::m_idCounter = 1;

    Password::Password()
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
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
        m_id=m_idCounter;
        m_idCounter++;
    }
    
    Password::Password(const std::string& url, const std::string& password):m_password(password), m_url(url)
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }
    
    std::string Password::encryption() const
    {
        std::string pass=m_password;
        for(int i = 0; i<m_password.length(); i++)
        { 
        int value = m_password[i]+5;
    
            if(value > 125)
            {
                int value2 = value-126;
                value=33+value2;
            }
            pass[i]=char(value);
       }
    
        return std::to_string(m_id) + "~" + pass + "~" + m_url + "~" + std::to_string(m_creationDate) + "~";
    }
    
    void Password::decryption(const std::string& data)
    {
        std::stringstream line(data);
        std::string segment;

        if(std::getline(line, segment, '~'))
        {
            m_id = std::stoi(segment);
            m_idCounter = m_id + 1;
        }

        if(std::getline(line, segment, '~'))
        {
            m_password = segment;
            for(int i = 0; i<segment.length(); i++)
            {
                int value=segment[i]-5;
                
                if(value<33)
                {
                    int value2 = value-32;
                    value=125+value2;
                }
                m_password[i]=char(value);
            }
        }
        
        if(std::getline(line, segment, '~'))
        {
            m_url = segment;
        }
        
        if(std::getline(line, segment, '~'))
        {
            long t = std::stol(segment);
            m_creationDate = static_cast<std::time_t>(t);
        }
    }
    
    bool Password::operator==(const Password& other) const
    {
        return (m_password==other.m_password && m_url==other.m_url);
    }
    
    std::ostream& operator<<(std::ostream& os, const Password& p)
    {
        std::string time = ctime(&p.m_creationDate);
        if(!time.empty() && time[time.length()-1] == '\n')
        {
            time.erase(time.end()-1);
        }
        os << p.m_id << "\n" << p.m_password << "\n" << p.m_url << "\n" << time << "\n";
    
        return os;
    }
    
    void Password::setPassword(const std::string& password)
    {
        if(!password.empty())
        {
            m_password=password;
        }
        else
        {
            throw std::invalid_argument("Password can not be empty");
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
    
    std::string Password::getCreationTime() const
    {
        std::string time = ctime(&m_creationDate);
        if(!time.empty() && time[time.length()-1] == '\n')
        {
            time.erase(time.end()-1);
        }
        return time;
    }
}