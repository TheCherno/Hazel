# The following is a list of breaking changes to yaml-cpp, by version #

# New API #

## HEAD ##

  * Throws an exception when trying to parse a negative number as an unsigned integer.
  * Supports the `as<int8_t>`/`as<uint8_t>`, which throws an exception when the value exceeds the range of `int8_t`/`uint8_t`.

## 0.6.0 ##

  * Requires C++11.

## 0.5.3 ##

_none_

## 0.5.2 ##

_none_

## 0.5.1 ##

  * `Node::clear` was replaced by `Node::reset`, which takes an optional node, similar to smart pointers.

## 0.5.0 ##

Initial version of the new API.

# Old API #

## 0.3.0 ##

_none_

## 0.2.7 ##

  * `YAML::Binary` now takes `const unsigned char *` for the binary data (instead of `const char *`).

## 0.2.6 ##

  * `Node::GetType()` is now `Node::Type()`, and returns an enum `NodeType::value`, where:
> > ` struct NodeType { enum value { Null, Scalar, Sequence, Map }; }; `
  * `Node::GetTag()` is now `Node::Tag()`
  * `Node::Identity()` is removed, and `Node::IsAlias()` and `Node::IsReferenced()` have been merged into `Node::IsAliased()`. The reason: there's no reason to distinguish an alias node from its anchor - whichever happens to be emitted first will be the anchor, and the rest will be aliases.
  * `Node::Read<T>` is now `Node::to<T>`. This wasn't a documented function, so it shouldn't break anything.
  * `Node`'s comparison operators (for example, `operator == (const Node&, const T&)`) have all been removed. These weren't documented either (they were just used for the tests), so this shouldn't break anything either.
  * The emitter no longer produces the document start by default - if you want it, you can supply it with the manipulator `YAML::BeginDoc`.

## 0.2.5 ##

This wiki was started with v0.2.5.