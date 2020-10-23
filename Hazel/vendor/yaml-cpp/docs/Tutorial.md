# Introduction #

A typical example, loading a configuration file, might look like this:

```cpp
YAML::Node config = YAML::LoadFile("config.yaml");

if (config["lastLogin"]) {
  std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";
}

const std::string username = config["username"].as<std::string>();
const std::string password = config["password"].as<std::string>();
login(username, password);
config["lastLogin"] = getCurrentDateTime();

std::ofstream fout("config.yaml");
fout << config;
```

# Basic Parsing and Node Editing #

All nodes in a YAML document (including the root) are represented by `YAML::Node`. You can check what kind it is:

```cpp
YAML::Node node = YAML::Load("[1, 2, 3]");
assert(node.Type() == YAML::NodeType::Sequence);
assert(node.IsSequence());  // a shortcut!
```

Collection nodes (sequences and maps) act somewhat like STL vectors and maps:

```cpp
YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
for (std::size_t i=0;i<primes.size();i++) {
  std::cout << primes[i].as<int>() << "\n";
}
// or:
for (YAML::const_iterator it=primes.begin();it!=primes.end();++it) {
  std::cout << it->as<int>() << "\n";
}

primes.push_back(13);
assert(primes.size() == 6);
```

and

```cpp
YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
  std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
}

lineup["RF"] = "Corey Hart";
lineup["C"] = "Jonathan Lucroy";
assert(lineup.size() == 5);
```

Querying for keys does **not** create them automatically (this makes handling optional map entries very easy)

```cpp
YAML::Node node = YAML::Load("{name: Brewers, city: Milwaukee}");
if (node["name"]) {
  std::cout << node["name"].as<std::string>() << "\n";
}
if (node["mascot"]) {
  std::cout << node["mascot"].as<std::string>() << "\n";
}
assert(node.size() == 2); // the previous call didn't create a node
```

If you're not sure what kind of data you're getting, you can query the type of a node:

```cpp
switch (node.Type()) {
  case Null: // ...
  case Scalar: // ...
  case Sequence: // ...
  case Map: // ...
  case Undefined: // ...
}
```

or ask directly whether it's a particular type, e.g.:

```cpp
if (node.IsSequence()) {
  // ...
}
```

# Building Nodes #

You can build `YAML::Node` from scratch:

```cpp
YAML::Node node;  // starts out as null
node["key"] = "value";  // it now is a map node
node["seq"].push_back("first element");  // node["seq"] automatically becomes a sequence
node["seq"].push_back("second element");

node["mirror"] = node["seq"][0];  // this creates an alias
node["seq"][0] = "1st element";  // this also changes node["mirror"]
node["mirror"] = "element #1";  // and this changes node["seq"][0] - they're really the "same" node

node["self"] = node;  // you can even create self-aliases
node[node["mirror"]] = node["seq"];  // and strange loops :)
```

The above node is now:

```yaml
&1
key: value
&2 seq: [&3 "element #1", second element]
mirror: *3
self: *1
*3 : *2
```

# How Sequences Turn Into Maps #

Sequences can be turned into maps by asking for non-integer keys. For example,

```cpp
YAML::Node node  = YAML::Load("[1, 2, 3]");
node[1] = 5;  // still a sequence, [1, 5, 3]
node.push_back(-3) // still a sequence, [1, 5, 3, -3]
node["key"] = "value"; // now it's a map! {0: 1, 1: 5, 2: 3, 3: -3, key: value}
```

Indexing a sequence node by an index that's not in its range will _usually_ turn it into a map, but if the index is one past the end of the sequence, then the sequence will grow by one to accommodate it. (That's the **only** exception to this rule.) For example,

```cpp
YAML::Node node = YAML::Load("[1, 2, 3]");
node[3] = 4; // still a sequence, [1, 2, 3, 4]
node[10] = 10;  // now it's a map! {0: 1, 1: 2, 2: 3, 3: 4, 10: 10}
```

# Converting To/From Native Data Types #

Yaml-cpp has built-in conversion to and from most built-in data types, as well as `std::vector`, `std::list`, and `std::map`. The following examples demonstrate when those conversions are used:

```cpp
YAML::Node node = YAML::Load("{pi: 3.14159, [0, 1]: integers}");

// this needs the conversion from Node to double
double pi = node["pi"].as<double>();

// this needs the conversion from double to Node
node["e"] = 2.71828;

// this needs the conversion from Node to std::vector<int> (*not* the other way around!)
std::vector<int> v;
v.push_back(0);
v.push_back(1);
std::string str = node[v].as<std::string>();
```

To use yaml-cpp with your own data types, you need to specialize the YAML::convert<> template class. For example, suppose you had a simple `Vec3` class:

```cpp
struct Vec3 { double x, y, z; /* etc - make sure you have overloaded operator== */ };
```

You could write

```cpp
namespace YAML {
template<>
struct convert<Vec3> {
  static Node encode(const Vec3& rhs) {
    Node node;
    node.push_back(rhs.x);
    node.push_back(rhs.y);
    node.push_back(rhs.z);
    return node;
  }

  static bool decode(const Node& node, Vec3& rhs) {
    if(!node.IsSequence() || node.size() != 3) {
      return false;
    }

    rhs.x = node[0].as<double>();
    rhs.y = node[1].as<double>();
    rhs.z = node[2].as<double>();
    return true;
  }
};
}
```

Then you could use `Vec3` wherever you could use any other type:

```cpp
YAML::Node node = YAML::Load("start: [1, 3, 0]");
Vec3 v = node["start"].as<Vec3>();
node["end"] = Vec3(2, -1, 0);
```