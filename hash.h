#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>

class hashTable {

 public:

  hashTable(int size = 0);

  int insert(const std::string &key, void *pv = NULL);

  bool contains(const std::string &key);

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return NULL.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  void *getPointer(const std::string &key, bool *b = NULL);

  // Set the pointer associated with the specified key.
  // Returns 0 on success,
  // 1 if the key does not exist in the hash table.
  int setPointer(const std::string &key, void *pv);

  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
  bool remove(const std::string &key);

 private:

  class hashItem {
  public:
    std::string key;
    bool isOccupied;
    bool isDeleted;
    void *pv;
  };

  int capacity; // The current capacity of the hash table.
  int filled; // Number of occupied items in the table.

  std::vector<hashItem> data; // The actual entries are here.

  int hash(const std::string &key);

  int findPos(const std::string &key);

  bool rehash();

  static unsigned int getPrime(int size);
};

#endif //_HASH_H
