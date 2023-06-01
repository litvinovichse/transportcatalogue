#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace svg {

struct Point {
    Point() = default;
    Point(double x, double y)
        : x(x)
        , y(y) {
    }
    double x = 0;
    double y = 0;
};

struct RenderContext {
    RenderContext(std::ostream& out)
        : out(out) {
    }

    RenderContext(std::ostream& out, int indent_step, int indent = 0)
        : out(out)
        , indent_step(indent_step)
        , indent(indent) {
    }

    RenderContext Indented() const {
        return {out, indent_step, indent + indent_step};
    }

    void RenderIndent() const {
        for (int i = 0; i < indent; ++i) {
            out.put(' ');
        }
    }

    std::ostream& out;
    int indent_step = 0;
    int indent = 0;
};

class ObjectContainer;
class Object;

class Drawable {
public:
    virtual void Draw(ObjectContainer& oc) const = 0;
    virtual ~Drawable() = default;
};

class ObjectContainer {
public:
    template<typename O>
    void Add(O obj);
    virtual void AddPtr(std::unique_ptr<Object>&& obj) = 0;
protected:
    std::vector<std::unique_ptr<Object>> vct;
};

class Object {
public:
    void Render(const RenderContext& context) const;
    virtual ~Object() = default;

private:
    virtual void RenderObject(const RenderContext& context) const = 0;
};
using Color = std::string;
inline const Color NoneColor{"none"};

enum class StrokeLineCap {
    BUTT,
    ROUND,
    SQUARE,
};

enum class StrokeLineJoin {
    ARCS,
    BEVEL,
    MITER,
    MITER_CLIP,
    ROUND,
};

inline std::ostream& operator<<(std::ostream& os, const StrokeLineCap& st){
    switch (st) {
    case StrokeLineCap::BUTT:
        os << "butt";
        break;
    case StrokeLineCap::ROUND:
        os << "round";
        break;
    case StrokeLineCap::SQUARE:
        os << "square";
        break;
    default:
        break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const StrokeLineJoin& st){
    switch (st) {
    case StrokeLineJoin::ARCS:
        os << "arcs";
        break;
    case StrokeLineJoin::BEVEL:
        os << "bevel";
        break;
    case StrokeLineJoin::MITER:
        os << "miter";
        break;
    case StrokeLineJoin::MITER_CLIP:
        os << "miter-clip";
        break;
    case StrokeLineJoin::ROUND:
        os << "round";
        break;
    default:
        break;
    }

    return os;
}

template <typename Owner>
class PathProps{
public:
    Owner& SetFillColor(Color color)
    {
        fill_color_ = std::move(color);
        return AsOwner();
    }
    Owner& SetStrokeColor(Color color) {
        stroke_color_ = std::move(color);
        return AsOwner();
    }
    Owner& SetStrokeWidth(double width){
        stroke_width_ = std::move(width);
        return AsOwner();
    }
    Owner& SetStrokeLineCap(StrokeLineCap line_cap){
        line_cap_ = line_cap;
        return AsOwner();
    }
    Owner& SetStrokeLineJoin(StrokeLineJoin line_join){
        line_join_ = line_join;
        return AsOwner();
    }
protected:
    ~PathProps() = default;
    void RenderAttrs(std::ostream &out) const {
        using namespace std::literals;

        if (fill_color_ != std::nullopt) {
            out << "fill=\""sv << fill_color_.value() << "\" "sv;
        }
        if (stroke_color_ != std::nullopt) {
            out << "stroke=\""sv << stroke_color_.value() << "\" "sv;
        }
        if (stroke_width_ != std::nullopt) {
            out << "stroke-width=\""sv << stroke_width_.value() << "\" "sv;
        }
        if (line_cap_ != std::nullopt) {
            out << "stroke-linecap=\""sv << line_cap_.value() << "\" "sv;
        }
        if (line_join_ != std::nullopt) {
            out << "stroke-linejoin=\""sv << line_join_.value() << "\" "sv;
        }
    }
private:
    Owner& AsOwner() {
        // static_cast безопасно преобразует *this к Owner&,
        // если класс Owner — наследник PathProps
        return static_cast<Owner&>(*this);
    }

    std::optional<Color> fill_color_;
    std::optional<Color> stroke_color_;
    std::optional<double> stroke_width_;
    std::optional<StrokeLineCap> line_cap_;
    std::optional<StrokeLineJoin> line_join_;
};

class Circle final : public Object, public PathProps<Circle>{
public:
    Circle& SetCenter(Point center);
    Circle& SetRadius(double radius);

private:
    void RenderObject(const RenderContext& context) const override;

    Point center_;
    double radius_ = 1.0;
};

class Polyline : public Object, public PathProps<Polyline> {
public:
    Polyline& AddPoint(Point point);

private:
    void RenderObject(const RenderContext& context) const override;
    std::vector<Point> dots_;
};

class Text  : public Object, public PathProps<Text> {
public:
    Text& SetPosition(Point pos);
    Text& SetOffset(Point offset);
    Text& SetFontSize(uint32_t size);
    Text& SetFontFamily(std::string font_family);
    Text& SetFontWeight(std::string font_weight);
    Text& SetData(std::string data);
private:
    void RenderObject(const RenderContext& context) const override;

    Point position_;
    Point offset_;
    uint32_t size_{ 1 };
    std::string font_family_;
    std::string font_weight_;
    std::string data_;
};

class Document : public ObjectContainer {
public:
    void AddPtr(std::unique_ptr<Object>&& obj) override  ;

    void Render(std::ostream& out) const;
};

template<typename O>
void ObjectContainer::Add(O obj)
{
    vct.push_back(std::make_unique<O>(obj));
}

}  // namespace svg
