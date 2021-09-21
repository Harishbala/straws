#include <iostream>
#include <string>

class CursorHandler {
    public:
    CursorHandler() = delete;
    CursorHandler(const std::string cursor_name)
        : _name(cursor_name) {
        }
    virtual ~CursorHandler() {};
    virtual void handle() {
        std::cout << "Cursor handler is invoked\n";
    }
    private:
    const std::string _name;
};
