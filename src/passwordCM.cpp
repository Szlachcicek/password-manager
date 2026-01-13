#include "passwordCM.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    unsigned int PasswordCM::m_idCounter = 1;

    PasswordCM::PasswordCM()
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }

    PasswordCM::PasswordCM(const std::string& url, const std::string& login):Password(url), m_login(login)
    {
        srand(static_cast<unsigned int>(time(0)));
        for(int i=0; i<m_passwordLength; i++)
        {
            int random = rand() % m_asciiLength+m_minAscii;
            m_password += random;
        }
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }

    PasswordCM::PasswordCM(const std::string& url, const std::string& login, const std::string& password):
    Password(url,password), m_login(login)
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }
    
    std::string PasswordCM::encryption() const
    {
        std::string pass=m_password;
        for(int i = 0; i<m_password.length(); i++)
        { 
        int value = m_password[i]+m_encryptValue;
    
            if(value > m_maxAscii)
            {
                int value2 = value-m_maxAscii-1;
                value=m_minAscii+value2;
            }
            pass[i]=char(value);
       }
    
        return std::to_string(m_id) + "~" + pass + "~" + m_url + "~" + std::to_string(m_creationDate) + "~"
        + m_login + "~";
    }

    void PasswordCM::decryption(const std::string& data)
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
                int value=segment[i]-m_encryptValue;
                
                if(value<m_minAscii)
                {
                    int value2 = value-m_minAscii+1;
                    value=m_maxAscii+value2;
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

        if(std::getline(line, segment, '~'))
        {
            m_login = segment;
        }
    }

    bool PasswordCM::operator==(const PasswordCM& other) const
    {
        return (m_password==other.m_password && m_url==other.m_url && m_login==other.m_login);
    }

    std::ostream& operator<<(std::ostream& os, const PasswordCM& p)
    {
        std::string time = ctime(&p.m_creationDate);
        if(!time.empty() && time[time.length()-1] == '\n')
        {
            time.erase(time.end()-1);
        }
        os << p.m_id << "\n" << p.m_password << "\n" << p.m_url << "\n" << time << "\n" << p.m_login << "\n";
    
        return os;
    }

    void PasswordCM::setLogin(const std::string& login)
    {
        if (login.find('~') != std::string::npos)
        {
            throw std::invalid_argument("login can not contain '~'!");
        }
        m_login=login;
    }

    std::string PasswordCM::getLogin() const
    {
        return m_login;
    }
}