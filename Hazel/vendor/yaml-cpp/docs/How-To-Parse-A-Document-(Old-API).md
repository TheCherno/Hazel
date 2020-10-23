_The following describes the old API. For the new API, see the [Tutorial](https://github.com/jbeder/yaml-cpp/wiki/Tutorial)._

## Contents ##


# Basic Parsing #

The parser accepts streams, not file names, so you need to first load the file. Since a YAML file can contain many documents, you can grab them one-by-one. A simple way to parse a YAML file might be:

```
#include <fstream>
#include "yaml-cpp/yaml.h"

int main()
{
    std::ifstream fin("test.yaml");
    YAML::Parser parser(fin);

    YAML::Node doc;
    while(parser.GetNextDocument(doc)) {
       // ...
    }

    return 0;
}
```

# Reading From the Document #

Suppose we have a document consisting only of a scalar. We can read that scalar like this:

```
YAML::Node doc;    // let's say we've already parsed this document
std::string scalar;
doc >> scalar;
std::cout << "That scalar was: " << scalar << std::endl;
```

How about sequences? Let's say our document now consists only of a sequences of scalars. We can use an iterator:

```
YAML::Node doc;    // already parsed
for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
    std::string scalar;
    *it >> scalar;
    std::cout << "Found scalar: " << scalar << std::endl;
}
```

... or we can just loop through:

```
YAML::Node doc;    // already parsed
for(unsigned i=0;i<doc.size();i++) {
    std::string scalar;
    doc[i] >> scalar;
    std::cout << "Found scalar: " << scalar << std::endl;
}
```

And finally maps. For now, let's say our document is a map with all keys/values being scalars. Again, we can iterate:

```
YAML::Node doc;    // already parsed
for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
    std::string key, value;
    it.first() >> key;
    it.second() >> value;
    std::cout << "Key: " << key << ", value: " << value << std::endl;
}
```

Note that dereferencing a map iterator is undefined; instead, use the `first` and `second` methods to get the key and value nodes, respectively.

Alternatively, we can pick off the values one-by-one, if we know the keys:

```
YAML::Node doc;    // already parsed
std::string name;
doc["name"] >> name;
int age;
doc["age"] >> age;
std::cout << "Found entry with name '" << name << "' and age '" << age << "'\n";
```

One thing to be keep in mind: reading a map by key (as immediately above) requires looping through all entries until we find the right key, which is an O(n) operation. So if you're reading the entire map this way, it'll be O(n^2). For small n, this isn't a big deal, but I wouldn't recommend reading maps with a very large number of entries (>100, say) this way.

## Optional Keys ##

If you try to access a key that doesn't exist, `yaml-cpp` throws an exception (see [When Something Goes Wrong](https://github.com/jbeder/yaml-cpp/wiki/How-To-Parse-A-Document-(Old-API)#When_Something_Goes_Wrong). If you have optional keys, it's often easier to use `FindValue` instead of `operator[]`:

```
YAML::Node doc;    // already parsed
if(const YAML::Node *pName = doc.FindValue("name")) {
    std::string name;
    *pName >> name;
    std::cout << "Key 'name' exists, with value '" << name << "'\n";
} else {
    std::cout << "Key 'name' doesn't exist\n";
}
```

# Getting More Complicated #

The above three methods can be combined to read from an arbitrary document. But we can make life a lot easier. Suppose we're reading 3-vectors (i.e., vectors with three components), so we've got a structure looking like this:

```
struct Vec3 {
    float x, y, z;
};
```

We can read this in one operation by overloading the extraction (>>) operator:

```
void operator >> (const YAML::Node& node, Vec3& v)
{
    node[0] >> v.x;
    node[1] >> v.y;
    node[2] >> v.z;
}

// now it's a piece of cake to read it
YAML::Node doc;    // already parsed
Vec3 v;
doc >> v;
std::cout << "Here's the vector: (" << v.x << ", " << v.y << ", " << v.z << ")\n";
```

# A Complete Example #

Here's a complete example of how to parse a complex YAML file:

`monsters.yaml`

```
- name: Ogre
  position: [0, 5, 0]
  powers:
    - name: Club
      damage: 10
    - name: Fist
      damage: 8
- name: Dragon
  position: [1, 0, 10]
  powers:
    - name: Fire Breath
      damage: 25
    - name: Claws
      damage: 15
- name: Wizard
  position: [5, -3, 0]
  powers:
    - name: Acid Rain
      damage: 50
    - name: Staff
      damage: 3
```

`main.cpp`

```
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// our data types
struct Vec3 {
   float x, y, z;
};

struct Power {
   std::string name;
   int damage;
};

struct Monster {
   std::string name;
   Vec3 position;
   std::vector <Power> powers;
};

// now the extraction operators for these types
void operator >> (const YAML::Node& node, Vec3& v) {
   node[0] >> v.x;
   node[1] >> v.y;
   node[2] >> v.z;
}

void operator >> (const YAML::Node& node, Power& power) {
   node["name"] >> power.name;
   node["damage"] >> power.damage;
}

void operator >> (const YAML::Node& node, Monster& monster) {
   node["name"] >> monster.name;
   node["position"] >> monster.position;
   const YAML::Node& powers = node["powers"];
   for(unsigned i=0;i<powers.size();i++) {
      Power power;
      powers[i] >> power;
      monster.powers.push_back(power);
   }
}

int main()
{
   std::ifstream fin("monsters.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
   for(unsigned i=0;i<doc.size();i++) {
      Monster monster;
      doc[i] >> monster;
      std::cout << monster.name << "\n";
   }

   return 0;
}
```

# When Something Goes Wrong #

... we throw an exception (all exceptions are derived from `YAML::Exception`). If there's a parsing exception (i.e., a malformed YAML document), we throw a `YAML::ParserException`:

```
try {
    std::ifstream fin("test.yaml");
    YAML::Parser parser(fin);
    YAML::Node doc;
    parser.GetNextDocument(doc);
    // do stuff
} catch(YAML::ParserException& e) {
    std::cout << e.what() << "\n";
}
```

If you make a programming error (say, trying to read a scalar from a sequence node, or grabbing a key that doesn't exist), we throw some kind of `YAML::RepresentationException`. To prevent this, you can check what kind of node something is:

```
    YAML::Node node;
    YAML::NodeType::value type = node.Type();  // should be:
                                               // YAML::NodeType::Null
                                               // YAML::NodeType::Scalar
                                               // YAML::NodeType::Sequence
                                               // YAML::NodeType::Map
```

# Note about copying `YAML::Node` #

Currently `YAML::Node` is non-copyable, so you need to do something like

```
    const YAML::Node& node = doc["whatever"];
```

This is intended behavior. If you want to copy a node, use the `Clone` function:

```
    std::auto_ptr<YAML::Node> pCopy = myOtherNode.Clone();
```

The intent is that if you'd like to keep a `YAML::Node` around for longer than the document will stay in scope, you can clone it and store it as long as you like.