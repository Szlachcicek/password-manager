#include "passwordBA.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    unsigned int PasswordBA::m_idCounter = 1;

    PasswordBA::PasswordBA()
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }

    PasswordBA::PasswordBA(const std::string& url, unsigned int clientNumber):Password(url), m_clientNumber(clientNumber)
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

    PasswordBA::PasswordBA(const std::string& url, unsigned int clientNumber, const std::string& password):
    Password(url,password), m_clientNumber(clientNumber)
    {
        time(&m_creationDate);
        m_id=m_idCounter;
        m_idCounter++;
    }
    
    std::string PasswordBA::encryption() const
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
        + std::to_string(m_clientNumber) + "~";
    }

    void PasswordBA::decryption(const std::string& data)
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
            m_clientNumber = std::stoi(segment);
        }
    }

    bool PasswordBA::operator==(const PasswordBA& other) const
    {
        return (m_password==other.m_password && m_url==other.m_url && m_clientNumber==other.m_clientNumber);
    }

    std::ostream& operator<<(std::ostream& os, const PasswordBA& p)
    {
        std::string time = ctime(&p.m_creationDate);
        if(!time.empty() && time[time.length()-1] == '\n')
        {
            time.erase(time.end()-1);
        }
        os << p.m_id << "\n" << p.m_password << "\n" << p.m_url << "\n" << time << "\n" << p.m_clientNumber << "\n";
    
        return os;
    }

    void PasswordBA::setClientNumber(const unsigned int clientNumber)
    {
        if(clientNumber>0)
        {
            m_clientNumber=clientNumber;
        }
        else
        {
            throw std::invalid_argument("Client number can not be 0");
        }
    }

    unsigned int PasswordBA::getClientNumber() const
    {
        return m_clientNumber;
    }
}