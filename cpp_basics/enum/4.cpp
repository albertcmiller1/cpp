// using a class after an enum like this specifies that an enumeration is strongly typeed and that its enumerators are scoped. 
// being separate types, enum classses help prevent accidental misue of constants. 

enum class Color { red, blue, green };
enum class Traffic_lisht { green, yellow, red };


Color col = Color::red;
Traffic_light light = Traffic_light::red;

