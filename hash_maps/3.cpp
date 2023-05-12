#include <iostream>
#include <string>
#include <unordered_map>

int main ()
{
  std::unordered_map<std::string,std::string> mymap = {
    {"us","United States"},
    {"uk","United Kingdom"},
    {"fr","France"},
    {"de","Germany"}
  };


    // A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.
    



  unsigned nbuckets = mymap.bucket_count();

  std::cout << "mymap has " << nbuckets << " buckets:\n";

  for (unsigned i=0; i<nbuckets; ++i) {
    std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
  }

  return 0;
}