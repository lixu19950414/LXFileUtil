//
//  Ini.hpp
//  FileUtil
//
//  Created by duoyi on 2017/6/29.
//  Copyright © 2017年 lixu. All rights reserved.
//

#ifndef Ini_hpp
#define Ini_hpp

#include <map>
#include <string>

namespace LX_FU {
    /**
     * INI files handlers.
     *
     * Name space LX_FU::INI
     * getIniConfigMap & saveIniConfigFile
     *
     */
    
    namespace INI {
        
        class IniConfig
        {
            
        public:
            IniConfig();
            IniConfig(const std::string& configName);
            ~IniConfig();
            
            bool saveToFile(const std::string& configName);
            bool loadFromFile(const std::string& configName);
            
            bool hasConf(const std::string& confName);
            std::string getConf(const std::string& confName);
            void setConf(const std::string& key, const std::string& value);
            
            
        private:
            std::map<std::string, std::string> m_mapIni;
        };
        
        IniConfig readIniConfigFromFile(const std::string& configName);
        
        bool saveIniConfigToFile(IniConfig& iniConfig, const std::string& configName);
    }
}


#endif /* Ini_hpp */
