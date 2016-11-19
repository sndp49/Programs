struct CommitNode
{
  string hash;
  string parent1Hash; // "" if none
  string parent2Hash; // "" if none
  uint64_t created;
  uint64_t lastModified;
  string author;
  void* delta;
}

CommitNode* getCommit(const string& hash); // provided; assume O(1)


bool doDFS(CommitNode* cur, unordered_set<string>& set, const string& hash2)
{
  if (set.find(cur->hash) != set.end())
    return false;

  set.insert(cur->hash);

  if (hash2.compare(cur->hash) == 0)
    return true;

  if (cur->parent1Hash.empty() && cur->parent2Hash.empty())
    return false;

  if (!cur->parent1Hash.empty())
  {
    if (doDFS(getCommit(cur->parent1Hash), hash2))
      return true;
  }

  return doDFS(getCommit(cur->parent2Hash), hash2));
}

// * hash1
// |\
// * |
// | *
// |/
// *
// |\
// | * hash2
// | <- super deep here



// contains(hash1, hash2) returns true if hash2 is in the ancestry of hash1
// otherwise false

bool contains(const string& hash1, const string& hash2)
{
  CommitNode* root = getCommit(hash1);

  unordered_set<string> visited;

  if (doDFS(root, visited, hash2))
    return true;

  return false;
}
