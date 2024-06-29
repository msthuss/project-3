#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Directory;

// class File
class File {
public:
    string name;
    string content;
    int size;


    // constructors
    File() = default;             //a default constructor
    File(const string &name);     //a constructor with name parameter


    string read();
    void write(const string &data);
    void deleteFile();
};



// class Directory
class Directory {
public:
    string name;
    Directory* parent;
    unordered_map<string, File> files;
    unordered_map<string, Directory*> subDirectories;

    Directory(string name, Directory* parent = nullptr);
    void addFile(const File &file);
    void addDirectory(Directory* dir);
    void listContents();
    void deleteFile(const string &fileName);
    void deleteDirectory(const string &dirName);
    Directory* getDirectory(const string &path);
};



// class FileSystem
class FileSystem {
private:
    Directory rootDirectory;
    Directory* currentDirectory;

public:
    FileSystem();
    void createFile(const string &path);
    void createDirectory(const string &path);
    string readFile(const string &path);
    void writeFile(const string &path, const string &data);
    void deleteFile(const string &path);
    void deleteDirectory(const string &path);
    void listDirectoryContents();
    void changeDirectory(const string &path);
    string getCurrentDirectoryPath();
};



// class  FileDescriptor
class FileDescriptor {
public:
    File *filePointer;
    string mode;

    FileDescriptor(File *file, string mode);

    void open(File *file, const string &mode);
    void close();
    File *getFile();
};

#endif 
