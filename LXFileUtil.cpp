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


#ifdef LX_FU_WINDOWS
#include <io.h>
#include <direct.h> 
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#ifdef LX_FU_WINDOWS
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

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
            && (path[1] == ':'))
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

	std::string getDirectory(const std::string & path)
	{
		std::string absolutePath = getAbsolutePath(path);
#ifdef LX_FU_WINDOWS
		int index = absolutePath.find_last_of('\\');
#else
		int index = absolutePath.find_last_of('/');
#endif // LX_FU_WINDOWS
		if (index >= 0)
		{
			return absolutePath.substr(0, index + 1);
		}
		return std::string();
	}

	std::string getFileName(const std::string & path)
	{
		std::string absolutePath = getAbsolutePath(path);
#ifdef LX_FU_WINDOWS
		int index = absolutePath.find_last_of('\\');
#else
		int index = absolutePath.find_last_of('/');
#endif // LX_FU_WINDOWS
		if (index >= 0)
		{
			return absolutePath.substr(index + 1, absolutePath.size());
		}
		return std::string();
	}

	bool makeDirectories(const std::string & path)
	{
		std::string directoryPath = getDirectory(getAbsolutePath(path));
		if (ACCESS(directoryPath.c_str(), 0) == 0) {
			return true;
		}
		else {
			int ret = MKDIR(directoryPath.c_str());
			if (ret == 0) {
				return true;
			}
			return false;
		}
	}

	Data* getDataFromFile(const std::string & path)
	{
		Data* d = new Data;
		d->initFromFile(path);
		return d;
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

	Data::Data():
	_loadSucceed(false)
	{
	}

	Data::~Data()
	{
		_sstream.clear();
	}

	bool Data::initFromFile(const std::string& path)
	{
		std::ifstream file;
		// ensures ifstream objects can throw exceptions:
		file.exceptions (std::ifstream::badbit);
		try
		{
		    // Open files
			file.open(getAbsolutePath(path));
		    // Read file's buffer contents into streams
		    _sstream << file.rdbuf();
			_loadSucceed = true;
		}
		catch (std::ifstream::failure e)
		{
		    std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
			std::cout << e.what() << std::endl;
		}
		return false;
	}
}

