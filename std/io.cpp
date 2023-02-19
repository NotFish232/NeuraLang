#include <iostream>

using namespace std;

template <class... Args>
void print(Args... args) {
    auto callable = [&](const auto &arg) -> void {
        cout << arg << ' ';
    };
    (callable(args), ...);
    cout << '\n';
}

string input(const string msg) {
    cout << msg;
    string inp;
    cin >> inp;
    return inp;
}

int main() {
    cout << "hello \n";
}
