#include "manager.hpp"
#include "password.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace ks
{
    Manager::Manager(){}

    Manager::Manager(const std::string& path):m_path(path){}

    void Manager::exporting(const Password& p)
    {
        std::ofstream file(m_path, std::ios::app);

        if(!file.is_open())
        {
            throw std::runtime_error("File did not open");
        }

        file << p.encryption() << "\n";
    }

    bool Manager::importing(Password& p)
    {
        std::ifstream file(m_path);

        if(!file.is_open())
        {
            throw std::runtime_error("File did not open");
        }

        std::string line;
        while(std::getline(file, line))
        {
            p.decryption(line);
        }

        if(!file.eof())
        {
            throw std::runtime_error("File reading filed");
        }

        file.close();
        return true;
    }

    std::ostream& operator<<(std::ostream& os, const Manager& m)
    {
        os << m.m_path << "\n";

        return os;
    }

    void Manager::setPath(const std::string& path)
    {
        if(m_path.length()>0)
        {
            m_path = path;
        }
        else
        {
            throw std::invalid_argument("Path can not be empty");
        }
    }

    std::string Manager::getPath() const
    {
        return m_path;
    }
}