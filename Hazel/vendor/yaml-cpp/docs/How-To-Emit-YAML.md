## Contents ##



# Basic Emitting #

The model for emitting YAML is `std::ostream` manipulators. A `YAML::Emitter` objects acts as an output stream, and its output can be retrieved through the `c_str()` function (as in `std::string`). For a simple example:

```cpp
#include "yaml-cpp/yaml.h"

int main()
{
   YAML::Emitter out;
   out << "Hello, World!";
   
   std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
   return 0;
}
```

# Simple Lists and Maps #

A `YAML::Emitter` object acts as a state machine, and we use manipulators to move it between states. Here's a simple sequence:

```cpp
YAML::Emitter out;
out << YAML::BeginSeq;
out << "eggs";
out << "bread";
out << "milk";
out << YAML::EndSeq;
```

produces

```yaml
- eggs
- bread
- milk
```

A simple map:

```cpp
YAML::Emitter out;
out << YAML::BeginMap;
out << YAML::Key << "name";
out << YAML::Value << "Ryan Braun";
out << YAML::Key << "position";
out << YAML::Value << "LF";
out << YAML::EndMap;
```

produces

```yaml
name: Ryan Braun
position: LF
```

These elements can, of course, be nested:

```cpp
YAML::Emitter out;
out << YAML::BeginMap;
out << YAML::Key << "name";
out << YAML::Value << "Barack Obama";
out << YAML::Key << "children";
out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
out << YAML::EndMap;
```

produces

```yaml
name: Barack Obama
children:
  - Sasha
  - Malia
```

# Using Manipulators #

To deviate from standard formatting, you can use manipulators to modify the output format. For example,

```cpp
YAML::Emitter out;
out << YAML::Literal << "A\n B\n  C";
```

produces

```yaml
|
A
 B
  C
```
and

```cpp
YAML::Emitter out;
out << YAML::Flow;
out << YAML::BeginSeq << 2 << 3 << 5 << 7 << 11 << YAML::EndSeq;
```

produces

```yaml
[2, 3, 5, 7, 11]
```

Comments act like manipulators:

```cpp
YAML::Emitter out;
out << YAML::BeginMap;
out << YAML::Key << "method";
out << YAML::Value << "least squares";
out << YAML::Comment("should we change this method?");
out << YAML::EndMap;
```

produces

```yaml
method: least squares  # should we change this method?
```

And so do aliases/anchors:

```cpp
YAML::Emitter out;
out << YAML::BeginSeq;
out << YAML::Anchor("fred");
out << YAML::BeginMap;
out << YAML::Key << "name" << YAML::Value << "Fred";
out << YAML::Key << "age" << YAML::Value << "42";
out << YAML::EndMap;
out << YAML::Alias("fred");
out << YAML::EndSeq;
```

produces

```yaml
- &fred
  name: Fred
  age: 42
- *fred
```

# STL Containers, and Other Overloads #
We overload `operator <<` for `std::vector`, `std::list`, and `std::map`, so you can write stuff like:

```cpp
std::vector <int> squares;
squares.push_back(1);
squares.push_back(4);
squares.push_back(9);
squares.push_back(16);

std::map <std::string, int> ages;
ages["Daniel"] = 26;
ages["Jesse"] = 24;

YAML::Emitter out;
out << YAML::BeginSeq;
out << YAML::Flow << squares;
out << ages;
out << YAML::EndSeq;
```

produces

```yaml
- [1, 4, 9, 16]
-
  Daniel: 26
  Jesse: 24
```

Of course, you can overload `operator <<` for your own types:

```cpp
struct Vec3 { int x; int y; int z; };
YAML::Emitter& operator << (YAML::Emitter& out, const Vec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}
```
and it'll play nicely with everything else.

# Using Existing Nodes #

We also overload `operator << ` for `YAML::Node`s in both APIs, so you can output existing Nodes. Of course, Nodes in the old API are read-only, so it's tricky to emit them if you want to modify them. So use the new API!

# Output Encoding #

The output is always UTF-8. By default, yaml-cpp will output as much as it can without escaping any characters. If you want to restrict the output to ASCII, use the manipulator `YAML::EscapeNonAscii`:

```cpp
emitter.SetOutputCharset(YAML::EscapeNonAscii);
```

# Lifetime of Manipulators #

Manipulators affect the **next** output item in the stream. If that item is a `BeginSeq` or `BeginMap`, the manipulator lasts until the corresponding `EndSeq` or `EndMap`. (However, within that sequence or map, you can override the manipulator locally, etc.; in effect, there's a "manipulator stack" behind the scenes.)

If you want to permanently change a setting, there are global setters corresponding to each manipulator, e.g.:

```cpp
YAML::Emitter out;
out.SetIndent(4);
out.SetMapStyle(YAML::Flow);
```

# When Something Goes Wrong #

If something goes wrong when you're emitting a document, it must be something like forgetting a `YAML::EndSeq`, or a misplaced `YAML::Key`. In this case, emitting silently fails (no more output is emitted) and an error flag is set. For example:

```cpp
YAML::Emitter out;
assert(out.good());
out << YAML::Key;
assert(!out.good());
std::cout << "Emitter error: " << out.GetLastError() << "\n";
```