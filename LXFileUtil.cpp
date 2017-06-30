/*
 *  FileUtil.cpp
 *  FileUtil
 *
 *  Created by duoyi on 2017/6/29.
 *  Copyright © 2017年 lixu. All rights reserved.
 *
 */

#include "LXFileUtil.h"
#include "LXFUDefines.h"

namespace LX_FU {
    void setPathPrefix(const std::string& path){
#ifdef LX_FU_WINDOWS
        if (path.back() == '\\') {
            g_strPathPrefix = path.substr(0, path.size() - 1);
            return;
        }
#else
        if (path.back() == '/') {
            g_strPathPrefix = path.substr(0, path.size() - 1);
            return;
        }
#endif
        g_strPathPrefix = path;
    }
    std::string getPathPrefix(){
        return g_strPathPrefix;
    }
    
    bool isAbsolutePath(const std::string& path){
#ifdef LX_FU_WINDOWS
        if (path.length() > 2
            && ((path[0] >= 'a' && path[0] <= 'z')||(path[0] >= 'A' && path[0] <= 'Z'))
            && (str[1] == ':'))
        {
            return true;
        }
        return false;
#else
        if (*(path.begin()) == '/') {
            return true;
        }
        return false;
#endif
    }
    
    std::string getAbsolutePath(const std::string& relativePath){
        if (isAbsolutePath(relativePath))
        {
            return relativePath;
        }
        else
        {
#ifdef LX_FU_WINDOWS
        return g_strPathPrefix + '\\' + relativePath;
#else
        return LX_FU::g_strPathPrefix + '/' + relativePath;
#endif
        }
    }
}

