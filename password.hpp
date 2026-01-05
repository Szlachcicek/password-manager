#pragma once

#include <string>
#include <ctime>
#include <iostream>

namespace ks{

    /**
    * Basic class to store only password and URL of website. Class automaticly adds time of creation and unique ID
    */
    class Password{
    protected:
        std::string m_password; ///< Password
        std::string m_url; ///< Address to website
        std::time_t m_creationDate; ///< Date of creation
        unsigned int m_id; ///< Unique identifier
        unsigned int m_idCounter ///< Counter for unique identifier

    public:
        /**
        * Default constructor
        */
        Password();

        /**
        * Constructor for generating password
        *
        * @param url    string with link to site
        */
        Password(const std::string& url);

        /**
        * Constructor for saving password
        *
        * @param pass   string with password to encrypt
        * @param url    string with link to site
        */
        Password(const std::string& password, const std::string& url);

        virtual ~Password();

        /**
        * Function for encrypting password
        *
        * @return formatted data ready to save in .txt file 
        */
        virtual std::string encryption() const;
        
        /**
        * Function for decrytping password
        *
        * @return data to class
        */
        virtual std::string decryption(const std::string& data);

        /**
        * Operator ==
        *
        * @return bool true (1) or false (0)
        */
        bool operator==(const Password& other) const;
        
        /**
        * Operator <<
        *
        * Allows to print class information on screen (std::cout)
        */
        friend std::ostream& operator<<(std::ostream& os, const Password& p);

        /**
        * Function to set new password
        *
        * Allows to change password
        *
        * @param password need to be password
        */
        void setPassword(const std::string& password);
        
        /**
        * Function to set new URL
        *
        * Allows to change URL
        *
        * @param url need to be url
        */
        void setURL(const std::string& url);
        
        
        /**
        * Function to get password
        *
        * @return password
        */
        std::string getPassword() const;

        /**
        * Function to get URL
        *
        * @return URL
        */
        std::string getURL() const;

        /**
        * Function to get time of password creation
        *
        * @return creation time (time_t)
        */
        std::time_t getCreationTime() const;
    };

}