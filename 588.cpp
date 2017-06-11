#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;
class FileSystem {
private:
    struct node{
        bool isFile;
        string content;
        unordered_map<string, struct node*> fileMap;
        node() : isFile(false), content(""){
        }
    };
    node* root;
public:
    FileSystem() {
        root = new node();
    }
    vector<string> parsePath(string& path) {
        vector<string> result;
        int st = 1, ed = 1;
        while (ed <= path.length()) {
            if (st != ed && (ed == path.length() || path[ed] == '/')) {
                result.push_back(path.substr(st, ed - st));
                st = ed + 1;
            }
            ed ++;
        }
        return result;
    }
    vector<string> ls(string path) {
        vector<string> pathList = parsePath(path);
        vector<string> result;
        node* curNode = root;
        for(string& dir : pathList) {
            curNode = curNode->fileMap[dir];
        }
        if (curNode->isFile) {
            return {pathList.back()};
        }

        for (auto &file : curNode->fileMap) {
            result.push_back(file.first);
        }
        sort(result.begin(), result.end());
        return result;
    }

    void mkdir(string path) {
        vector<string> pathList = parsePath(path);
        node* curNode = root;
        for(string& dir : pathList) {
            if (curNode->fileMap.find(dir) == curNode->fileMap.end()) {
                curNode->fileMap[dir] = new node();
            }
            curNode = curNode->fileMap[dir];
        }
    }

    void addContentToFile(string filePath, string content) {
        vector<string> pathList = parsePath(filePath);
        node* curNode = root;
        for(string& dir : pathList) {
            if (curNode->fileMap.find(dir) == curNode->fileMap.end()) {
                curNode->fileMap[dir] = new node();
            }
            curNode = curNode->fileMap[dir];
        }
        curNode->isFile = true;
        curNode->content += content;
    }
    string readContentFromFile(string filePath) {
        vector<string> pathList = parsePath(filePath);
        node* curNode = root;
        for (string & dir : pathList) {
            curNode = curNode->fileMap[dir];
        }
        return curNode->content;
    }
    bool getRoot() {
        return root->isFile;
    }
};
int main() {
    FileSystem fs;
    vector<string> ss = fs.ls("/");
    for(string& str : ss) {
        cout<< str<<endl;
    }
    fs.mkdir("/jinxin/j/x");
    fs.addContentToFile("/jinxin/j/x/jx", "you are a good man!");
    cout << fs.readContentFromFile("/jinxin/j/x/jx") <<endl;
    ss = fs.ls("/jinxin/j/x");
    for(string& str : ss) {
        cout<< str<<endl;
    }
}
