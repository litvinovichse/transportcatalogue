#include "svg.h"

namespace svg {

using namespace std::literals;

void Object::Render(const RenderContext& context) const {
    context.RenderIndent();

    // Делегируем вывод тега своим подклассам
    RenderObject(context);

    context.out << std::endl;
}

// ---------- Circle ------------------

Circle& Circle::SetCenter(Point center)  {
    center_ = center;
    return *this;
}

Circle& Circle::SetRadius(double radius)  {
    radius_ = radius;
    return *this;
}

void Circle::RenderObject(const RenderContext& context) const {
    auto& out = context.out;
    out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
    out << "r=\""sv << radius_ << "\" "sv;
    RenderAttrs(out);
    out << "/>"sv;
}

// ---------- Polyline ------------------

Polyline &Polyline::AddPoint(Point point)
{
    dots_.push_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext &context) const
{
    auto& out = context.out;
    out << "<polyline points=\""sv;
    bool firstLine = true;
    for (auto a : dots_){
        if (firstLine){
            out << a.x<<","<<a.y;
            firstLine = false;
        } else {
            out << " ";
            out << a.x<<","<<a.y;
        }
    }
    out  << "\" "sv;
    RenderAttrs(out);
    out << "/>"sv;
}

// ---------- Text ------------------

Text &Text::SetPosition(Point pos)
{
    position_ = pos;
    return *this;
}

Text &Text::SetOffset(Point offset)
{
    offset_ = offset;
    return *this;
}

Text &Text::SetFontSize(uint32_t size)
{
    size_ = size;
    return *this;
}

Text &Text::SetFontFamily(std::string font_family)
{
    font_family_ = font_family;
    return *this;
}

Text &Text::SetFontWeight(std::string font_weight)
{
    font_weight_ = font_weight;
    return *this;
}

Text &Text::SetData(std::string data)
{
    data_ = data;
    return *this;
}

void Text::RenderObject(const RenderContext &context) const
{
    auto& out = context.out;
    out << "<text x=\""sv << position_.x << "\" y=\""sv << position_.y << "\" dx=\""sv << offset_.x << "\" dy=\""sv << offset_.y << "\" font-size=\""sv
        << size_ << "\" " ;
    if (!font_family_.empty()){

        out <<"font-family=\""sv << font_family_ <<  "\" ";

    }
    if(!font_weight_.empty()){

        out << "font-weight=\""sv << font_weight_ << "\"";

    }
    RenderAttrs(out);
    out << ">" << data_ << "</text>";
}

// ---------- Document ------------------

void Document::AddPtr(std::unique_ptr<Object> &&obj)
{
    vct.push_back(std::move(obj));
}

void Document::Render(std::ostream &out) const
{
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"sv << std::endl;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"sv << std::endl;
    RenderContext dtx(std::cout, 2, 2);
    for (const auto& a : vct){
        a->Render(dtx);
    }
    out << "</svg>"sv;
}

void PrintColor(std::ostream &out, Rgb &rgb)
{
    out << "rgb("sv << std::to_string(rgb.red) << "," << std::to_string(rgb.green) << "," <<  std::to_string(rgb.blue) << ")";
}

void PrintColor(std::ostream &out, Rgba &rgba)
{
    out << "rgba("sv << std::to_string(rgba.red) << "," << std::to_string(rgba.green) << "," <<  std::to_string(rgba.blue) << "," << rgba.opacity << ")";
}

void PrintColor(std::ostream &out, std::monostate)
{
    out << "none";
}

void PrintColor(std::ostream &out, std::string &color)
{
    out << color;
}

}  // namespace svg
