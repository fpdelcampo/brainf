#include <iostream>
#include <stack>
#include <fstream>

std::vector<int> jump_table;
std::string program;
int size;

void build_jump_table() {
    std::stack<int> st;
    for(int i = 0; i < size; i++) {
        if(program[i] == '[') {
            st.push(i);
        }
        else if(program[i] == ']') {
            if(st.empty()) {
                std::cerr << "Unmatched ']' at position " << i << std::endl;
                exit(1);
            }
            int last = st.top();
            st.pop();
            jump_table[last] = i;
            jump_table[i] = last;
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        std::getline(std::cin, program);
    }
    else if(argc == 2) {
        std::ifstream file(argv[1]);
        if(!file.is_open()) {
            std::cerr << "File not found" << std::endl;
            return -1;
        }
        std::string line;
        while(getline(file, line)) {
            program += line;
        }
        file.close();
    }


    char data[30000] = {0};
    // std::getline(std::cin, program);
    int dp = 0;
    int ip = 0;
    size = program.size();
    jump_table.assign(size, 0);

    build_jump_table();

    while(ip < size) {
        char command = program[ip];
        switch (command) {
            case '>':
                if(dp >= 29999) {
                    std::cerr << "Pointer out of bounds" << std::endl;
                    exit(1);
                }
                dp++;
                break;
            case '<':
                if(dp == 0) {
                    std::cerr << "Pointer out of bounds" << std::endl;
                    exit(1);
                }
                dp--;
                break;
            case '+':
                data[dp]++;
                break;
            case '-':
                data[dp]--;
                break;
            case '.':
                std::cout << data[dp];
                break;
            case ',':
                data[dp] = std::cin.get();
                break;
            case '[':
                if(data[dp] == 0) {
                    ip = jump_table[ip];
                }
                break;
            case ']':
                if(data[dp] != 0) {
                    ip = jump_table[ip];
                }
                break;
            default:
                break;
        }
        ip++;
    }
    std::cout << std::endl;
    return 0;
}