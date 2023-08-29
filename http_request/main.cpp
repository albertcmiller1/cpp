#include <iostream>
#include "include/HTTPRequest.hpp"
using namespace std;

void get_request(){
    try{
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{"http://bjnhhj5gd2.execute-api.us-east-1.amazonaws.com/Prod/products"};
        // http::Request request{"http://3.95.214.132:5001/curr_price"};

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e){
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void post_request(){
    try{
        http::Request request{"https://bjnhhj5gd2.execute-api.us-east-1.amazonaws.com/Prod/product"};
        const std::string body = "{\"foo\": 1, \"bar\": \"baz\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
        });
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e){
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

int main()
{
    cout << "Hello World" << endl;
    get_request();
    // post_request();

    return 0;
}