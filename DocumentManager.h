#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class DocumentManager {
public:
    DocumentManager();
    void addDocument(const std::string &name, int id, int license_limit);
    void addPatron(int patronID);
    int search(const std::string &name);
    bool borrowDocument(int docid, int patronID);
    void returnDocument(int docid, int patronID);

private:
    struct Document {
        std::string name;
        int license_limit;
        int current_borrowed;
    };
    std::unordered_map<int, Document> documents;
    std::unordered_map<std::string, int> document_name_to_id;
    std::unordered_map<int, std::unordered_set<int>> patrons;
};

#endif // DOCUMENTMANAGER_H
