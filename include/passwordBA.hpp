#pragma once

#include "password.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    class PasswordBA : public Password
    {
        friend class Manager;

    private:
        static unsigned int m_idCounter; ///< Counter for unique identifier for classes

    protected:
        unsigned int m_clientNumber; ///< Client number for logging

    public:
        /**
        * @brief Default constructor
        * 
        * Setting only time of creation
        */
        PasswordBA();
        
        /**
         * @brief Constructor for generating password
         * 
         * Setting time of creation, URL of website, client number and generating password
         * 
         * @param url string with link to site
         * @param clientNumber unsigned integer with client number
         */
        PasswordBA(const std::string& url, unsigned int clientNumber);

        /**
         * @brief Constructor for saving password
         * 
         * Setting time of creation, URL of website, client number and password
         * 
         * @param url string with link to site
         * @param password string with password to encrypt
         * @param clientNumber unsigned integer with client number
         */
        PasswordBA(const std::string& url, unsigned int clientNumber, const std::string& password);

        /**
        * @brief Function for encrypting password
        *
        * @return formatted all data ready to save in .txt file 
        */
        std::string encryption() const override;

        /**
        * @brief Function for decrytping password
        *
        * @return data to class
        */
        void decryption(const std::string& data) override;

        /**
        * @brief Operator ==
        *
        * @return bool true or false if objects are identicall (m_url, m_password, m_clientNumber)
        */
        bool operator==(const PasswordBA& other) const;
        
        /**
        * @brief Operator <<
        *
        * Allows to print class information on screen (std::cout)
        * 
        * @return id, password, url, client number, creation date (even when empty)
        */
        friend std::ostream& operator<<(std::ostream& os, const PasswordBA& p);

        /**
        * @brief Function to set new client number
        *
        * Allows to change client number
        *
        * @param clientNumber need to be client number
        */
        void setClientNumber(const unsigned int clientNumber);
        
        /**
        * @brief Function to get client number
        *
        * @return client number
        */
        unsigned int getClientNumber() const;
    };
}