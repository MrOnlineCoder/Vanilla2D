/*
	Original code by Foaly: https://github.com/SFML/SFML/wiki/Source:-Settings-Parser
*/

#ifndef V2D_CFGPARSER_H
#define V2D_CFGPARSER_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

class ConfigParser 
{
public:
    ConfigParser();
    ~ConfigParser();

    bool loadFromFile(const std::string& filename);
    bool saveToFile();

    bool isChanged() const;
    
    template<typename T>
    void get(const std::string& key, T & value) const;
    template<typename T>
    void get(const std::string& key, std::vector<T> &value) const;
    
    template<typename T>
    void set(const std::string &key, const T value);
    template<typename T>
    void set(const std::string& key, const std::vector<T> value);

    void print() const;

private:
    
    //return the string in the type of T
    template<typename T>
    T convertToType(const std::string &input) const;
    //return string of type T
    template<typename T>
    std::string convertToStr(const T input) const;
    
    bool read();
    bool write() const;
    std::pair<std::string, std::string> parseLine(const std::string &line) const;

    bool m_isChanged;
    std::string m_filename;
    std::map<std::string, std::string> m_data;
    const std::locale m_locale;
};


template<typename T>
inline std::string ConfigParser::convertToStr(T input) const {
    throw "Unsupported type supplied, either change types, or write a correct conversion function for the template type.";
}

template<>
inline std::string ConfigParser::convertToStr<std::string>(std::string value) const {
    return value;
}

template<>
inline std::string ConfigParser::convertToStr<const char*>(const char* value) const {
    return std::string(value);
}

template<>
inline std::string ConfigParser::convertToStr<bool>(bool value) const {
    return (value) ? "TRUE" : "FALSE";
}

template<>
inline std::string ConfigParser::convertToStr<char>(char value) const {
    std::string tmp = "";
    tmp = value;
    return tmp;
}

template<>
inline std::string ConfigParser::convertToStr<int>(int value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string ConfigParser::convertToStr<float>(float value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string ConfigParser::convertToStr<short>(short value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<>
inline std::string ConfigParser::convertToStr<double>(double value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
inline T ConfigParser::convertToType(const std::string &input) const {
    throw "Unconvertable type encountered, please use a different type, or define the handle case in ConfigParser.hpp";
}

template<>
inline int ConfigParser::convertToType<int>(const std::string &input) const {
    int value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline double ConfigParser::convertToType<double>(const std::string &input) const {
    double value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline float ConfigParser::convertToType<float>(const std::string &input) const {
    float value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline short ConfigParser::convertToType<short>(const std::string &input) const {
    short value;
    std::stringstream ss(input);
    ss >> value;
    
    return value;
}

template<>
inline bool ConfigParser::convertToType<bool>(const std::string &input) const {
    return input == "TRUE" ? true : false;
}

template<>
inline char ConfigParser::convertToType<char>(const std::string &input) const {
    return input[0];
}

template<>
inline std::string ConfigParser::convertToType<std::string>(const std::string &input) const {
    return input;
}

template<typename T>
inline void ConfigParser::get(const std::string& key, T &value) const {
    auto it = m_data.find(key);
    
    if (it != m_data.end()){
        value = convertToType<T>(it->second);
    }
}

/**
 * This method tries to read the value of a key into a vector. The values have to be
 * seperated by comma. The vector is cleared before it is filled.
 */
template<typename T>
inline void ConfigParser::get(const std::string& key, std::vector<T> &value) const {
    auto it = m_data.find(key);
    if (it != m_data.end()){
        
        std::string output;
        std::istringstream parser(it->second);
        
        value.clear();
        
        //split by comma
        while (getline(parser, output, ',')){
            value.push_back(convertToType<T>(output));
        }
    }
}

template<typename T>
inline void ConfigParser::set(const std::string& key, const T value) {
    // the [] operator replaces the value if the key is found, if not it creates a new element
    m_data[key] = convertToStr<T>(value);
    m_isChanged = true;
}

template<typename T>
inline void ConfigParser::set(const std::string &key, const std::vector<T> value) {
    // transform the vector into a string that seperates the elements with a comma
    std::string valueAsString;
    for (size_t i = 0; i < value.size() - 1; ++i){
        valueAsString += convertToStr<T>(value.at(i)) + ",";
    }
    valueAsString += convertToStr<T>(value.back());

    // the [] operator replaces the value if the key is found, if not it creates a new element
    m_data[key] = valueAsString;
    m_isChanged = true;
}

#endif