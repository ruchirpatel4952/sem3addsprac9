class DocumentManager:
    def __init__(self):
        # Dictionary to store documents: {docid: (name, license_limit, current_borrowed)}
        self.documents = {}
        # Dictionary to map document names to their ids for fast search: {name: docid}
        self.document_name_to_id = {}
        # Dictionary to store patrons: {patronID: set(docids)}
        self.patrons = {}
    
    def addDocument(self, name, id, license_limit):
        if id in self.documents:
            raise ValueError("Document ID already exists.")
        self.documents[id] = (name, license_limit, 0)
        self.document_name_to_id[name] = id
    
    def addPatron(self, patronID):
        if patronID in self.patrons:
            raise ValueError("Patron ID already exists.")
        self.patrons[patronID] = set()
    
    def search(self, name):
        return self.document_name_to_id.get(name, 0)
    
    def borrowDocument(self, docid, patronID):
        if patronID not in self.patrons:
            return False
        if docid not in self.documents:
            return False
        name, license_limit, current_borrowed = self.documents[docid]
        if current_borrowed >= license_limit:
            return False
        # Borrow the document
        self.documents[docid] = (name, license_limit, current_borrowed + 1)
        self.patrons[patronID].add(docid)
        return True
    
    def returnDocument(self, docid, patronID):
        if patronID not in self.patrons or docid not in self.documents:
            return
        if docid in self.patrons[patronID]:
            name, license_limit, current_borrowed = self.documents[docid]
            self.documents[docid] = (name, license_limit, current_borrowed - 1)
            self.patrons[patronID].remove(docid)
