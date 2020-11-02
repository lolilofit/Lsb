#include <iostream>
#include <fstream>
#include <cmath>
#include "lodepng.h"

void decode(int size) {
    std::fstream new_txt(R"(C:\Users\User\CLionProjects\untitled\\new_text.txt)", std::ios::out|std::ios::binary|std::ios::app);

    std::vector<unsigned char> out;
    unsigned w;
    unsigned h;
    std::string new_file_name(R"(C:\Users\User\CLionProjects\untitled\new_image.png)");
    unsigned error = lodepng::decode(out,  w, h, new_file_name);

    if(error != 0)
        return;

    unsigned char one_byte = 0;
    int bit_cur = 0;

    for(int i = 0; i < out.size() && i < size; i ++) {
        unsigned char val = (out[i]) & 1;
        one_byte += val * (unsigned char)std::pow(2, bit_cur);
        bit_cur++;
        if(bit_cur == 8) {
            new_txt.write((char*)&one_byte, sizeof(unsigned char));
            bit_cur = 0;
            one_byte = 0;
        }
    }

    new_txt.close();
}

int lsb() {
    uint8_t one_byte;
    uint8_t bit_cur = 0;
    unsigned int h;
    unsigned int w;
    std::vector<unsigned char> out;
    std::string filename("C:\\Users\\User\\CLionProjects\\untitled\\image.png");

    unsigned error = lodepng::decode(out,  w, h, filename);
    std::ifstream insert_file(R"(C:\Users\User\CLionProjects\untitled\file)",std::ios::in|std::ios::binary);

    if(error != 0 || !insert_file.is_open())
        return 0;

    int inserted_size = 0;
    for(int i = 0; i < out.size(); i ++) {
        if(insert_file.tellg() == -1) {
            break;
        }

        if(bit_cur%8 == 0) {
            insert_file.read((char*)&one_byte, sizeof(uint8_t));

            if(insert_file.tellg() == -1) {
                break;
            }

            bit_cur = 0;
        }

        out[i] = (out[i] & (~(1))) |  ((one_byte >> bit_cur) & 1);
        bit_cur++;
        inserted_size++;
    }

    std::string new_file_name("C:\\Users\\User\\CLionProjects\\untitled\\new_image.png");
    lodepng::encode(new_file_name, out, w, h);
    return inserted_size;
}

int main() {
    int size = lsb();

    decode(size);

    return 0;
}