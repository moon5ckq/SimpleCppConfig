#ifndef __CONFIG_BASE_H__
#define __CONFIG_BASE_H__

#include <string>
#include <map>
#include <typeinfo>
#include <utility>
#include <fstream>

#define V(v) this->values[#v] = std::make_pair<std::string, void*>(typeid(v).name(), &v)

class ConfigBase {
private:
    typedef std::map<std::string, std::pair<std::string, void*> > ConfigMap;
public:
    inline void load(const std::string& configFile) {
        std::ifstream ifs(configFile.c_str());
        
        for (std::string line; std::getline(ifs, line); ) {
            if (line.empty() || line[0] == '#') continue;
            size_t i = line.find('=');
            if (std::string::npos == i) {
                throw "Invalid line encountered in config file.";
            }
            
            std::string key = strip(line.substr(0, i)),
                        value = strip(line.substr(i + 1));
            
            if (values.count(key)) {
                std::string& type = values[key].first;
                void* p = values[key].second;
            #if __cplusplus > 199711L
                if (type == typeid(int).name()) {
                    *((int*)p) = std::stoi(value);
                } else if (type == typeid(long).name()) {
                    *((long*)p) = std::stol(value);
                } else if (type == typeid(long long).name()) {
                    *((long long*)p) = std::stoll(value);
                } else if (type == typeid(unsigned long).name()) {
                    *((unsigned long*)p) = std::stoul(value);
                } else if (type == typeid(unsigned long long).name()) {
                    *((unsigned long long*)p) = std::stoull(value);
                } else if (type == typeid(float).name()) {
                    *((float*)p) = std::stof(value);
                } else if (type == typeid(double).name()) {
                    *((double*)p) = std::stod(value);
                } else if (type == typeid(long double).name()) {
                    *((long double*)p) = std::stold(value);
                } else {
                    *((std::string*)p) = value;
                }
            #else
                if (type == typeid(int).name()) {
                    sscanf(value.c_str(), "%d", p);
                } else if (type == typeid(long).name()) {
                    sscanf(value.c_str(), "%ld", p);
                } else if (type == typeid(long long).name()) {
                    sscanf(value.c_str(), "%lld", p);
                } else if (type == typeid(unsigned long).name()) {
                    sscanf(value.c_str(), "%lu", p);
                } else if (type == typeid(unsigned long long).name()) {
                    sscanf(value.c_str(), "%llu", p);
                } else if (type == typeid(float).name()) {
                    sscanf(value.c_str(), "%f", p);
                } else if (type == typeid(double).name()) {
                    sscanf(value.c_str(), "%lf", p);
                } else if (type == typeid(long double).name()) {
                    sscanf(value.c_str(), "%Lf", p);
                } else {
                    *((std::string*)p) = value;
                }
            #endif
            }
        }
    }
    
protected:
    static inline std::string strip(const std::string& str) {
        static const char* WHITE_SPACE = " \t\n\r";
        size_t l = str.find_first_not_of(WHITE_SPACE),
                r = str.find_last_not_of(WHITE_SPACE);
        return str.substr(l, r - l + 1);
    }

    ConfigMap values;
};

#endif//__CONFIG_BASE_H__