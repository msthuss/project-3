#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FileSystem.hpp"

TEST_CASE("Create and Delete File", "[filesystem]") {
    FileSystem fs;
    fs.createFile("test.txt");
    REQUIRE(fs.readFile("test.txt") == "");
    fs.writeFile("test.txt", "Hello, World!");
    REQUIRE(fs.readFile("test.txt") == "Hello, World!");
    fs.deleteFile("test.txt");
    REQUIRE(fs.readFile("test.txt") == "File not found!");
}

TEST_CASE("Create and Delete Directory", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("testDir");
    fs.changeDirectory("testDir");
    REQUIRE(fs.getCurrentDirectoryPath() == "-/testDir");
    fs.changeDirectory("..");
    fs.deleteDirectory("testDir");
    fs.changeDirectory("testDir");
    REQUIRE(fs.getCurrentDirectoryPath() == "-");
}

TEST_CASE("Write and Read File in Subdirectory", "[filesystem]") {
    FileSystem fs;
    fs.createDirectory("subDir");
    fs.changeDirectory("subDir");
    fs.createFile("test.txt");
    fs.writeFile("test.txt", "Subdirectory File");
    REQUIRE(fs.readFile("test.txt") == "Subdirectory File");
    fs.changeDirectory("..");
    fs.deleteDirectory("subDir");
    REQUIRE(fs.readFile("subDir/test.txt") == "File not found!");
}
