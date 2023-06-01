#include "json.h"

using namespace std;

namespace json {

namespace {

Node LoadNode(istream& input);

std::string LoadLiteral(std::istream& input) {
    std::string str;

    while (std::isalpha(input.peek())) {
        str.push_back(static_cast<char>(input.get()));
    }
    return str;
}

Node LoadBool(std::istream& input) {
    const auto str = LoadLiteral(input);

    if (str == "true") {
        return Node(true);
    }
    else if (str == "false") {
        return Node(false);
    }
    else {
        throw ParsingError("");
    }
}

Node LoadNull(std::istream& input) {
    if (auto literal = LoadLiteral(input); literal == "null"sv) {
        return Node(nullptr);
    }
    else {
        throw ParsingError("");
    }
}

Node LoadArray(std::istream& input) {
    std::vector<Node> array;

    for (char ch; input >> ch && ch != ']';) {
        if (ch != ',') {
            input.putback(ch);
        }

        array.push_back(LoadNode(input));
    }

    if (!input) {
        throw ParsingError(""s);
    }

    return Node(array);
}

Node LoadNumber(std::istream& input) {
    std::string number;

    auto read_char = [&number, &input] {
        number += static_cast<char>(input.get());

        if (!input) {
            throw ParsingError("unable to read number"s);
        }
    };

    auto read_digits = [&input, read_char] {

        if (!std::isdigit(input.peek())) {
            throw ParsingError("A digit is expected"s);
        }
        else {
            while (std::isdigit(input.peek())) {
                read_char();
            }
        }
    };

    if (input.peek() == '-') {
        read_char();
    }

    if (input.peek() == '0') {
        read_char();
    }
    else {
        read_digits();
    }

    bool is_int = true;
    if (input.peek() == '.') {
        read_char();
        read_digits();
        is_int = false;
    }

    if (int ch = input.peek(); ch == 'e' || ch == 'E') {
        read_char();

        if (ch = input.peek(); ch == '+' || ch == '-') {
            read_char();
        }

        read_digits();
        is_int = false;
    }

    try {
        if (is_int) {
            try {
                return Node(std::stoi(number));

            }
            catch (...) {}
        }
        return Node(std::stod(number));

    }
    catch (...) {
        throw ParsingError("unable to convert "s + number + " to number"s);
    }
}

Node LoadString(std::istream& input) {
    auto it = std::istreambuf_iterator<char>(input);
    auto end = std::istreambuf_iterator<char>();
    std::string str;

    while (true) {
        if (it == end) {
            throw ParsingError("unable to parse string");
        }

        const char ch = *it;
        if (ch == '"') {
            ++it;
            break;

        }
        else if (ch == '\\') {
            ++it;
            if (it == end) {
                throw ParsingError("-parse string");
            }

            const char esc_ch = *(it);
            switch (esc_ch) {
            case 'n':
                str.push_back('\n');
                break;
            case 't':
                str.push_back('\t');
                break;
            case 'r':
                str.push_back('\r');
                break;
            case '"':
                str.push_back('"');
                break;
            case '\\':
                str.push_back('\\');
                break;
            default:
                throw ParsingError("invalid"s + esc_ch);
            }

        }
        else if (ch == '\n' || ch == '\r') {
            throw ParsingError("-line end"s);
        }
        else {
            str.push_back(ch);
        }

        ++it;
    }

    return Node(str);
}

Node LoadDict(std::istream& input) {
    Dict dictionary;

    for (char ch; input >> ch && ch != '}';) {

        if (ch == '"') {
            std::string key = LoadString(input).AsString();

            if (input >> ch && ch == ':') {

                if (dictionary.find(key) != dictionary.end()) {
                    throw ParsingError("error '"s + key + "'found");
                }

                dictionary.emplace(std::move(key), LoadNode(input));

            }
            else {
                throw ParsingError(": error '"s + ch + "' found"s);
            }

        }
        else if (ch != ',') {
            throw ParsingError("',' error'"s + ch + "' found"s);
        }
    }

    if (!input) {
        throw ParsingError("-parse dictionary"s);
    }
    else {
        return Node(dictionary);
    }

}

Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
        return LoadArray(input);
    }
    else if (c == '{') {
        return LoadDict(input);
    }
    else if (c == '"') {
        return LoadString(input);
    }
    else if (c == 't' || c == 'f') {
        input.putback(c);
        return LoadBool(input);
    }
    else if (c == 'n') {
        input.putback(c);
        return LoadNull(input);
    }
    else {
        input.putback(c);
        return LoadNumber(input);
    }
}

}  // namespace


//vvvvvvvvvv ----конструкторы---- vvvvvvvvvvv
/*Node::Node()
    {
        variant_ = nullptr; в .h выставлен default;
    }*/

Node::Node(int value)
{
    variant_ = value;
}

Node::Node(double d)
{
    variant_ = d;
}

Node::Node(std::string value)
{
    variant_ = std::move(value);
}

Node::Node(bool b)
{
    variant_ = b;
}

Node::Node(Array array)
{
    variant_ = std::move(array);
}

Node::Node(Dict map)
{
    variant_ = std::move(map);
}

Node::Node(std::nullptr_t)
{
    variant_ = nullptr;
}
//^^^^^^^^^^^ ----конструкторы---- ^^^^^^^^^^


//vvvvvvvvvvvv ----checktype---- vvvvvvvvvv
bool Node::IsInt() const
{
    return std::holds_alternative<int>(variant_);
}

bool Node::IsDouble() const
{
    return IsInt() || IsPureDouble();
    //return CheckType<double>() || CheckType<int>();
}

bool Node::IsPureDouble() const
{
    return std::holds_alternative<double>(variant_); //просто добавляется double без проверок, проверки в isDouble

}

bool Node::IsString() const
{
    return std::holds_alternative<std::string>(variant_);
    //return CheckType<std::string>();
}

bool Node::IsBool() const
{
    return std::holds_alternative<bool>(variant_);
    //return CheckType<bool>();
}

bool Node::IsArray() const
{
    return std::holds_alternative<Array>(variant_);
    //return CheckType<Array>();
}

bool Node::IsMap() const
{
    return std::holds_alternative<Dict>(variant_);
    //return CheckType<Dict>();
}

bool Node::IsNull() const
{
    return std::holds_alternative<std::nullptr_t>(variant_);
    //    return CheckType<nullptr_t>();
}

//^^^^^^^^^^^ ----checktype---- ^^^^^^^^^^


//vvvvvvvvvvvv ----Getter---- vvvvvvvvvv
int Node::AsInt() const
{
    if (!CheckType<int>()) {
        throw std::logic_error("");
    }
    return get<int>(variant_);

}

double Node::AsDouble() const
{
    if (!IsDouble()) {
        throw std::logic_error("");
    }
    else if (IsPureDouble()) {
        return std::get<double>(variant_);
    }
    return AsInt();
}

const string& Node::AsString() const
{
    if (!CheckType<string>()) {
        throw std::logic_error("");
    }
    return get<string>(variant_);
}

bool Node::AsBool() const
{
    if (!CheckType<bool>()) {
        throw std::logic_error("");
    }
    return get<bool>(variant_);
}

const Array& Node::AsArray() const
{
    if (!CheckType<Array>()) {
        throw std::logic_error("");
    }
    return get<Array>(variant_);
}

const Dict& Node::AsMap() const
{
    if (!CheckType<Dict>()) {
        throw std::logic_error("");
    }
    return get<Dict>(variant_);
}

Document::Document(Node root)
    : root_(std::move(root)) {
}

const Node& Document::GetRoot() const {
    return root_;
}

Document Load(istream& input) {

    return Document{ LoadNode(input) };
}

struct PrintContext {                   //Вставлено с подсказки
    std::ostream& out;
    int indent_step = 4;
    int indent = 0;

    void PrintIndent() const {
        for (int i = 0; i < indent; ++i) {
            out.put(' ');
        }
    }

    [[nodiscard]] PrintContext Indented() const {
        return { out,
                indent_step,
                indent + indent_step };
    }
};

void PrintNode(const Node& node, const PrintContext& context);


void PrintString(const std::string& value, std::ostream& out) {
    out.put('"');

    for (const char ch : value) {
        switch (ch) {
        case '\r':
            out << R"(\r)";
            break;
        case '\n':
            out << R"(\n)";
            break;
        case '"':
            out << R"(\")";
            break;
        case '\\':
            out << R"(\\)";
            break;
        default:
            out.put(ch);
            break;
        }
    }

    out.put('"');
}

template <typename Value>
void PrintValue(const Value& value, const PrintContext& context) {
    context.out << value;
}

template <>
void PrintValue<std::string>(const std::string& value, const PrintContext& context) {
    PrintString(value, context.out);
}

void PrintValue(const std::nullptr_t&, const PrintContext& context) {
    context.out << "null"s;
}

void PrintValue(bool value, const PrintContext& context) {
    context.out << std::boolalpha << value;
}

void PrintValue(Array nodes, const PrintContext& context) {
    std::ostream& out = context.out;
    out << "[\n"sv;
    bool first = true;
    auto inner_context = context.Indented();

    for (const Node& node : nodes) {
        if (first) {
            first = false;
        }
        else {
            out << ",\n"sv;
        }

        inner_context.PrintIndent();
        PrintNode(node, inner_context);
    }

    out.put('\n');
    context.PrintIndent();
    out.put(']');
}

void PrintValue(Dict nodes, const PrintContext& context) {
    std::ostream& out = context.out;
    out << "{\n"sv;
    bool first = true;
    auto inner_context = context.Indented();

    for (const auto& [key, node] : nodes) {
        if (first) {
            first = false;
        }
        else {
            out << ",\n"sv;
        }

        inner_context.PrintIndent();
        PrintString(key, context.out);
        out << ": "sv;
        PrintNode(node, inner_context);
    }

    out.put('\n');
    context.PrintIndent();
    out.put('}');
}

void PrintNode(const Node& node, const PrintContext& context) {
    std::visit([&context](const auto& value) {
        PrintValue(value, context);
    }, node.GetValue());
}

void Print(const Document& document, std::ostream& output) {
    PrintNode(document.GetRoot(), PrintContext{ output });
}

}  // namespace json
