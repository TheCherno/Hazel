# Encodings and `yaml-cpp` #

`yaml-cpp` will parse any file as specified by the [YAML 1.2 spec](http://www.yaml.org/spec/1.2/spec.html#id2570322). Internally, it stores all strings in UTF-8, and representation is done with UTF-8. This means that in

```
std::string str;
node >> str;
```

`str` will be UTF-8. Similarly, if you're accessing a map by string key, you need to pass the key in UTF-8. If your application uses a different encoding, you need to convert to and from UTF-8 to work with `yaml-cpp`. (It's possible we'll add some small conversion functions, but for now it's restricted.)

---

For convenience, Richard Weeks has kindly provided a google gadget that converts Unicode to a string literal. It's a Google Gadget, so unfortunately it does not work on GitHub. Patches welcome to port it to a usable format here:

```
<wiki:gadget url="http://hosting.gmodules.com/ig/gadgets/file/111180078345548400783/c-style-utf8-encoder.xml"/>
```