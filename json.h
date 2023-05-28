#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

namespace json {

class Node;
// Сохраните объявления Dict и Array без изменения
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Node {
public:

    using Value = std::variant<std::nullptr_t, int, double, std::string, bool, Array, Dict>;


    Node() = default;

    Node(int value);
    Node(double d);
    Node(std::string value);
    Node(bool b);
    Node(Array array);
    Node(Dict map);
    Node(std::nullptr_t);


    bool IsInt() const;
    bool IsDouble() const;
    bool IsPureDouble() const;
    bool IsString() const;
    bool IsBool() const;
    bool IsArray() const;
    bool IsMap() const;
    bool IsNull() const;

    template<typename T>
    bool CheckType() const;


    int AsInt() const;
    double AsDouble() const;
    const std::string& AsString() const;
    bool AsBool() const;
    const Array& AsArray() const;
    const Dict& AsMap() const;

    const Value& GetValue() const {
        return variant_;
    };
    //^^^^^^^^^^^ ----Getter---- ^^^^^^^^^^



private:
    Value variant_;
};


inline bool operator==(const Node& lhs, const Node& rhs) {
    return lhs.GetValue() == rhs.GetValue();
}
inline bool operator!=(const Node& lhs, const Node& rhs) {
    return !(lhs == rhs);
}


template<typename T>
bool Node::CheckType() const
{
    return std::holds_alternative<T>(variant_);

}

class Document {
public:
    explicit Document(Node root);

    const Node& GetRoot() const;

private:
    Node root_;
};

Document Load(std::istream& input);

inline bool operator==(const Document& lhs, const Document& rhs) { //перегрузка нужная
    return lhs.GetRoot() == rhs.GetRoot();
}
inline bool operator!=(const Document& lhs, const Document& rhs) {
    return !(lhs == rhs);
}

void Print(const Document& doc, std::ostream& output);


}  // namespace json
