/*
 *  FileUtil.hpp
 *  FileUtil
 *
 *  Created by duoyi on 2017/6/29.
 *  Copyright © 2017年 lixu. All rights reserved.
 *
 */

#ifndef FileUtil_
#define FileUtil_

#include <string>
#include <iostream>
#include <map>

/* The classes below are exported */
//#pragma GCC visibility push(default)

namespace LX_FU {
    
    /**
     * Global path prefix of fileutil to fix relative paths.
     *
     */
    
    static std::string g_strPathPrefix = "/";

    void setPathPrefix(const std::string& path);
    
    std::string getPathPrefix();
    
    std::string getAbsolutePath(const std::string& relativePath);
    
    bool isAbsolutePath(const std::string& path);
    
}


//#pragma GCC visibility pop
#endif
