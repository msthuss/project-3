#include "FileSystem.hpp"
#include <sstream>

using namespace std;



// ===============File class implementation=================
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



// ==================Directory class implementation======================
Directory::Directory(string name, Directory* parent) : name(name), parent(parent) {}

void Directory::addFile(const File &file) {
    files[file.name] = file;
}

void Directory::addDirectory(Directory* dir) {
    subDirectories[dir->name] = dir;
}

void Directory::listContents() {
    for (const auto &file : files) {
        cout << "File: " << file.second.name << endl;
    }
    for (const auto &dir : subDirectories) {
        cout << "Directory: " << dir.second->name << endl;
    }
}

void Directory::deleteFile(const string &fileName) {
    files.erase(fileName);
}

void Directory::deleteDirectory(const string &dirName) {
    subDirectories.erase(dirName);
}

Directory* Directory::getDirectory(const string &path) {
    if (path.empty()) {
        return this;
    }
    
    istringstream ss(path);
    string token;
    Directory* currentDir = this;
    while (getline(ss, token, '/')) {
        if (currentDir->subDirectories.find(token) != currentDir->subDirectories.end()) {
            currentDir = currentDir->subDirectories[token];
        } else {
            return nullptr;
        }
    }
    return currentDir;
}



// =============FileDescriptor class implementation=========
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



//============ File System Implementation===========
FileSystem::FileSystem() : rootDirectory("root"), currentDirectory(&rootDirectory) {}

void FileSystem::createFile(const string &path) {
    File file(path);
    currentDirectory->addFile(file);
}

void FileSystem::createDirectory(const string &path) {
    Directory* dir = new Directory(path, currentDirectory);
    currentDirectory->addDirectory(dir);
}

string FileSystem::readFile(const string &path) {
    if (currentDirectory->files.find(path) != currentDirectory->files.end()) {
        return currentDirectory->files[path].read();
    } else {
        return "File not found!";
    }
}

void FileSystem::writeFile(const string &path, const string &data) {
    if (currentDirectory->files.find(path) != currentDirectory->files.end()) {
        currentDirectory->files[path].write(data);
    } else {
        cout << "File not found!" << endl;
    }
}

void FileSystem::deleteFile(const string &path) {
    currentDirectory->deleteFile(path);
}

void FileSystem::deleteDirectory(const string &path) {
    currentDirectory->deleteDirectory(path);
}

void FileSystem::listDirectoryContents() {
    currentDirectory->listContents();
}

void FileSystem::changeDirectory(const string &path) {
    Directory* dir = rootDirectory.getDirectory(path);
    if (dir != nullptr) {
        currentDirectory = dir;
        cout << "Directory changed successfully";
    } else {
        cout << "Directory not found!" << endl;
    }
}

string FileSystem::getCurrentDirectoryPath() {
    // string path = "";
    Directory* dir = currentDirectory;
    // while (dir != &rootDirectory) {
    //     path = "/" + dir->name + path;
    //     dir = dir->parent;
    // }
    return dir->name;
}



// =====================Main Function=============
int main() {
    FileSystem fs;
    int choice;
    string path, data;

    while (true) {
       
        cout << "\n\n=================================\n";
        cout << "File System Menu:\n";
        cout << "1. Create Directory\n";
        cout << "2. Create File\n";
        cout << "3. Read File\n";
        cout << "4. Write File\n";
        cout << "5. Delete File\n";
        cout << "6. Delete Directory\n";
        cout << "7. List Directory Contents\n";
        cout << "8. Change Directory\n";
        cout << "9. Show current directory. \n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter directory name: ";
                cin >> path;
                fs.createDirectory(path);
                cout << "Directory Created Successfully.";
                break;
                
            case 2:
                cout << "Enter file name: ";
                cin >> path;
                fs.createFile(path);
                cout << "File Created Successfully.";
                break;
                
            case 3:
                cout << "Enter file name: ";
                cin >> path;
                cout << "File contents: " << fs.readFile(path) << endl;
                break;

            case 4:
                cout << "Enter file name: ";
                cin >> path;
                cout << "Enter data: ";
                cin.ignore();
                getline(cin, data);
                fs.writeFile(path, data);
                break;

            case 5:
                cout << "Enter file name: ";
                cin >> path;
                fs.deleteFile(path);
                cout << "File Deleted Successfully.";
                break;

            case 6:
                cout << "Enter directory name: ";
                cin >> path;
                fs.deleteDirectory(path);
                cout << "Directory deleted Successfully.";
                break;

            case 7:
                fs.listDirectoryContents();
                break;

            case 8:
                cout << "Enter directory path: ";
                cin >> path;
                fs.changeDirectory(path);
                break;

            case 9:
                cout << "\nCurrent Directory: " << fs.getCurrentDirectoryPath() << endl;
                break;

            case 10:
                cout<< "Exiting...";
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}