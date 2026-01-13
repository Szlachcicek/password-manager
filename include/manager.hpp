#pragma once

#include "password.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace ks{

    /**
    * Class to manage writing and reading files for class Password
    */
    class Manager{
    private:
        std::string m_path; ///< Path to file with encrypted data
    public:

        /**
        * Template to export encrypted data to class Password
        *
        * @param database vector of objects from class Password. Calls T::encryption to save string to file
        */
        template <typename T>
        void exporting(const std::vector<T>& database)
        {
            std::vector<T>toSort = database;

            std::sort(toSort.begin(), toSort.end(), [](const T& a, const T& b){return a.m_id<b.m_id;});

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

        /**
        * Template to import encrypted data
        *
        * @return vector of T
        */
        template <typename T>
        std::vector<T> importing()
        {
            unsigned int maxId{};
            std::vector<T>  passwordsList;
            std::ifstream file(m_path);

            if(!file.is_open())
            {
                throw std::runtime_error("File did not open");
            }

            std::string line;
            while(std::getline(file, line))
            {
                T temp;
                temp.decryption(line);
                passwordsList.push_back(temp);
                if(temp.m_id>maxId)
                {
                    maxId = temp.m_id;
                }
            }
                T::m_idCounter = maxId+1;

            if(file.bad())
            {
                throw std::runtime_error("File reading filed");
            }

            file.close();

            return passwordsList;
        }

        /**
        * Default constructor
        */
        Manager();

        /**
        * Parametric constructor to set path
        *
        * @param path string with path to encrypted file
        */
        Manager(const std::string& path);

        /**
        * Operator <<
        *
        * Allows to print class information on screen (std::cout)
        */
        friend std::ostream& operator<<(std::ostream& os, const Manager& m);

        /**
        * Function to set path
        *
        * Allows to set path
        *
        * @param path need to be path to encrypted file
        */
        void setPath(const std::string& path);

        /**
        * Function to get path
        *
        * @return path
        */
        std::string getPath() const;
        };

}