#include "manager.hpp"
#include "password.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace ks
{
    Manager::Manager(){}

    Manager::Manager(const std::string& path):m_path(path){}

    void Manager::exporting(const std::vector<Password>& database)
    {
        std::vector<Password>toSort = database;

        std::sort(toSort.begin(), toSort.end(), [](const Password& a, const Password& b){return a.m_id<b.m_id;});

        std::ofstream file(m_path, std::ios::trunc);

        if(!file.is_open())
        {
            throw std::runtime_error("File did not open");
        }

        for(const auto& d : toSort)
        {
            file << d.encryption() << "\n";
        }

        file.close();
    }

    std::vector<Password> Manager::importing()
    {
        unsigned int maxId{};
        std::vector<Password>  passwordsList;
        std::ifstream file(m_path);

        if(!file.is_open())
        {
            throw std::runtime_error("File did not open");
        }

        std::string line;
        while(std::getline(file, line))
        {
            Password temp;
            temp.decryption(line);
            passwordsList.push_back(temp);
            if(temp.m_id>maxId)
            {
                maxId = temp.m_id;
            }
        }
            Password::m_idCounter = maxId+1;

        if(file.bad())
        {
            throw std::runtime_error("File reading filed");
        }

        file.close();

        return passwordsList;
    }

    std::ostream& operator<<(std::ostream& os, const Manager& m)
    {
        os << m.m_path << "\n";

        return os;
    }

    void Manager::setPath(const std::string& path)
    {
        if(path.length()>0)
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