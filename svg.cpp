#include "svg.h"
 
namespace svg {
 
using namespace std::literals;
// ---------- Rgb/Rgba ------------------   
 
Rgb::Rgb(uint8_t red, uint8_t green, uint8_t blue) : red_(red)
                                                   , green_(green)
                                                   , blue_(blue) {}  
    
Rgba::Rgba(uint8_t red, uint8_t green, uint8_t blue, double opacity) : red_(red)
                                                                     , green_(green)
                                                                     , blue_(blue)
                                                                     , opacity_(opacity) {}
 
// ---------- Color ------------------
    
inline void print_color(std::ostream& out, Rgb& rgb) {
    out << "rgb("sv << static_cast<short>(rgb.red_) << ","sv
                    << static_cast<short>(rgb.green_) << ","sv 
                    << static_cast<short>(rgb.blue_) << ")"sv;
}
    
inline void print_color(std::ostream& out, Rgba& rgba) {
    out << "rgba("sv << static_cast<short>(rgba.red_) << ","sv 
                     << static_cast<short>(rgba.green_) << ","sv 
                     << static_cast<short>(rgba.blue_) << ","sv 
                     << (rgba.opacity_) << ")"sv;
}
    
inline void print_color(std::ostream& out, std::monostate) {
    out << "none"sv;
}
 
inline void print_color(std::ostream& out, std::string& color) {
    out << color;
}
    
std::ostream& operator<<(std::ostream& out, const Color& color) {
    std::visit([&out](auto value) {
            print_color(out, value);
    }, color);
    
    return out;
} 
    