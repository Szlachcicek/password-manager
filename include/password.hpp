#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks{

    /**
    * Basic class to store only password and URL of website. Class automaticly adds time of creation and unique ID.
    * 
    * Uses <vector> for importing and exporting
    * 
    * If file with database exists, firstly import data by using ks::Manager::imporing() to vector
    */
    class Password{
        friend class Manager;

    private:
        static unsigned int m_idCounter; ///< Counter for unique identifier for classes

    protected:
        std::string m_password; ///< Password
        std::string m_url; ///< Address to website
        std::time_t m_creationDate; ///< Date of creation
        unsigned int m_id; ///< Unique identifier
        static constexpr int m_encryptValue = 5; ///< Value for encoding/decoding
        static constexpr int m_minAscii = 33; ///< Minimal ASCII value for letters, numbers and charakters
        static constexpr int m_maxAscii = 125; ///< Maximal ASCII value for letters, numbers and charakters
        static constexpr int m_passwordLength = 15; ///< Variable to select generated password length
        static constexpr int m_asciiLength = 92; ///< Variable to select used characters in ASCII

    public:
        /**
        * @brief Default constructor
        * 
        * Setting only time of creation
        */
        Password();

        /**
        * @brief Constructor for generating password
        * 
        * Setting time of creation, URL of website and generating password
        *
        * @param url string with link to site
        */
        Password(const std::string& url);

        /**
        * @brief Constructor for saving password
        * 
        * Setting time of creation, URL of website and password
        *
        * @param password string with password to encrypt
        * @param url string with link to site
        */
        Password(const std::string& url, const std::string& password);

        /**
        * @brief Function for encrypting password
        *
        * @return formatted all data ready to save in .txt file 
        */
        virtual std::string encryption() const;
        
        /**
        * @brief Function for decrytping password
        *
        * @return data to class
        */
        virtual void decryption(const std::string& data);

        /**
        * @brief Operator ==
        *
        * @return bool true or false if objects are identicall (m_url, m_password)
        */
        virtual bool operator==(const Password& other) const;
        
        /**
        * @brief Operator <<
        *
        * Allows to print class information on screen (std::cout)
        * 
        * @return id, password, url, creation date (even when empty)
        */
        friend std::ostream& operator<<(std::ostream& os, const Password& p);

        /**
        * @brief Function to set new password
        *
        * Allows to change password
        *
        * @param password need to be password
        */
        void setPassword(const std::string& password);
        
        /**
        * @brief Function to set new URL
        *
        * Allows to change URL
        *
        * @param url need to be url
        */
        void setURL(const std::string& url);
        
        
        /**
        * @brief Function to get password
        *
        * @return password
        */
        std::string getPassword() const;

        /**
        * @brief Function to get URL
        *
        * @return URL
        */
        std::string getURL() const;

        /**
        * @brief Function to get time of password creation
        *
        * @return creation time (time_t)
        */
        std::string getCreationTime() const;
    };

}