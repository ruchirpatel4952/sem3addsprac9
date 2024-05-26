#include "DocumentManager.h"
#include <stdexcept>

DocumentManager::DocumentManager() {}

void DocumentManager::addDocument(const std::string &name, int id, int license_limit) {
    if (documents.find(id) != documents.end()) {
        throw std::invalid_argument("Document ID already exists.");
    }
    documents[id] = {name, license_limit, 0};
    document_name_to_id[name] = id;
}

void DocumentManager::addPatron(int patronID) {
    if (patrons.find(patronID) != patrons.end()) {
        throw std::invalid_argument("Patron ID already exists.");
    }
    patrons[patronID] = std::unordered_set<int>();
}

int DocumentManager::search(const std::string &name) {
    auto it = document_name_to_id.find(name);
    if (it != document_name_to_id.end()) {
        return it->second;
    }
    return 0; // Document not found
}

bool DocumentManager::borrowDocument(int docid, int patronID) {
    if (patrons.find(patronID) == patrons.end()) {
        return false; // Invalid patronID
    }
    auto doc_it = documents.find(docid);
    if (doc_it == documents.end()) {
        return false; // Invalid docid
    }
    Document &doc = doc_it->second;
    if (doc.current_borrowed >= doc.license_limit) {
        return false; // License limit reached
    }
    // Borrow the document
    doc.current_borrowed++;
    patrons[patronID].insert(docid);
    return true;
}

void DocumentManager::returnDocument(int docid, int patronID) {
    if (patrons.find(patronID) == patrons.end() || documents.find(docid) == documents.end()) {
        return; // Invalid patronID or docid
    }
    auto &borrowed_docs = patrons[patronID];
    if (borrowed_docs.find(docid) != borrowed_docs.end()) {
        Document &doc = documents[docid];
        doc.current_borrowed--;
        borrowed_docs.erase(docid);
    }
}
