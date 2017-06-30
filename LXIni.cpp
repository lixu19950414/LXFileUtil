//
//  Ini.cpp
//  FileUtil
//
//  Created by duoyi on 2017/6/29.
//  Copyright © 2017年 lixu. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "LXIni.h"
#include "LXFileUtil.h"


namespace LX_FU {
    namespace INI{
        IniConfig::IniConfig()
        {
            
        };
        
        IniConfig::IniConfig(const std::string& configName)
        {
            loadFromFile(configName);
        }
        
        IniConfig::~IniConfig()
        {
            
        }
        
        bool IniConfig::IniConfig::hasConf(const std::string& confName){
            if (m_mapIni.find(confName) != m_mapIni.end()) {
                return true;
            }
            return false;
        };
        
        std::string IniConfig::IniConfig::getConf(const std::string& confName){
            auto it = m_mapIni.find(confName);
            if (it != m_mapIni.end()) {
                return it->second;
            }
            return "";
        };
        
        void IniConfig::IniConfig::setConf(const std::string& key, const std::string& value){
            auto it = m_mapIni.find(key);
            if (it != m_mapIni.end()) {
                m_mapIni[key] = value;
                return;
            }
            m_mapIni.emplace(key, value);
        };
        
        bool IniConfig::saveToFile(const std::string& configName){
            std::ofstream of(LX_FU::getAbsolutePath(configName), std::ios::out);
            if (of) {
                for (auto it: m_mapIni){
                    of.write(it.first.c_str(), it.first.size());
                    of.write("=", 1);
                    of.write(it.second.c_str(), it.second.size());
                    of.write("\n", 1);
                }
                of.close();
                return true;
            }
            
            std::cout<<"Error::saveConfigToFile: cannot open file with name -- "<<configName<<std::endl;
            return false;
        };
        
        bool IniConfig::loadFromFile(const std::string& configName){
            std::ifstream config(LX_FU::getAbsolutePath(configName), std::ios::in);
            char buffer[32];
            if (config) {
                while (!config.eof()) {
                    config.getline(buffer, 32);
                    std::string tmp(buffer);
                    if (*tmp.begin() == '#') {
                        continue;
                    }
                    unsigned long pos = tmp.find_first_of('=');
                    if (pos > 0) {
                        std::string key = tmp.substr(0, pos);
                        std::string value = tmp.substr(pos + 1, tmp.size());
                        m_mapIni.emplace(key, value);
                    }
                }
                config.close();
                return true;
            }
            return false;
        }
        
        IniConfig readIniConfigFromFile(const std::string& configName){
            return IniConfig(configName);
        }
        
        bool saveIniConfigToFile(IniConfig& iniConfig, const std::string& configName){
            return iniConfig.saveToFile(configName);
        }
    }
}
