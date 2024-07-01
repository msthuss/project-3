#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Directory class
class Directory {
public:
    string name;
    unordered_map<string, File> files;
    unordered_map<string, Directory> directories;

    Directory(string name);

    void addFile(const File &file);
    void addDirectory(const Directory &dir);
    void listContents();
    void deleteFile(const string &fileName);
    void deleteDirectory(const string &dirName);
};

// File class
class File {
public:
    string name;
    string content;
    int size;

    // Constructors
    File() = default;  // Default constructor
    File(const string &name);  // Constructor with name parameter

    string read();
    void write(const string &data);
    void deleteFile();
};



// FileSystem class
class FileSystem {
public:
    Directory rootDirectory;

    FileSystem();

    void createFile(const string &path);
    string readFile(const string &path);
    void writeFile(const string &path, const string &data);
    void deleteFile(const string &path);
    void listDirectoryContents(const string &path);
};

// FileDescriptor class
class FileDescriptor {
public:
    File *filePointer;
    string mode;

    FileDescriptor(File *file, string mode);

    void open(File *file, const string &mode);
    void close();
    File *getFile();
};

// File class implementation

File::File(const string &name) : name(name), size(0) {}

string File::read() {
    return content;
}

void File::write(const string &data) {
    content = data;
    size = data.size();
}

void File::deleteFile() {
    content.clear();
    size = 0;
}

// Directory class implementation

Directory::Directory(string name) : name(name) {}

void Directory::addFile(const File &file) {
    files[file.name] = file;
}

void Directory::addDirectory(const Directory &dir) {
    directories[dir.name] = dir;
}

void Directory::listContents() {
    for (const auto &file : files) {
        cout << "File: " << file.second.name << endl;
    }
    for (const auto &dir : directories) {
        cout << "Directory: " << dir.second.name << endl;
    }
}

void Directory::deleteFile(const string & fileName) {
    files.erase(fileName);
}

void Directory::deleteDirectory(const string & dirName) {
    directories.erase(dirName);
}

// FileSystem class implementation

FileSystem::FileSystem() : rootDirectory("root") {}

void FileSystem::createFile(const string &path) {
    File file(path);
    rootDirectory.addFile(file);
}

string FileSystem::readFile(const string &path) {
    return rootDirectory.files[path].read();
}

void FileSystem::writeFile(const string & path, const string & data) {
    rootDirectory.files[path].write(data);
}

void FileSystem::deleteFile(const string & path) {
    rootDirectory.deleteFile(path);
}

void FileSystem::listDirectoryContents(const string &path) {
    if (path == "root") {
        rootDirectory.listContents();
    }
}

// FileDescriptor class implementation

FileDescriptor::FileDescriptor(File *file, string mode) : filePointer(file), mode(mode) {}

void FileDescriptor::open(File *file, const string &mode) {
    filePointer = file;
    this->mode = mode;
}

void FileDescriptor::close() {
    filePointer = nullptr;
    mode.clear();
}

File *FileDescriptor::getFile() {
    return filePointer;
}

// Main function for testing purposes

int main() {
    FileSystem fs;

    // Example usage
    fs.createFile("file1.txt");
    fs.writeFile("file1.txt", "Hello, World!");
    fs.listDirectoryContents("root");

    return 0;
}
