#include <iostream>
#include <fstream>

using namespace std;

struct struct_pomocznicze {
    int poz, licz_znak;
    char next_char;
};

int main() {
    int size_slownik;
    char *slownik;
    cout << "Podaj dlugosc slownika:";
    cin >> size_slownik;
    slownik = new char[size_slownik + 1];
    slownik[size_slownik] = {'\0'};
    fstream in_data, out_data;
    in_data.open("C:\\Users\\szymon\\CLionProjects\\LZ77 koder\\cmake-build-debug\\wyjście_zakodowane.txt", ios::in);
    out_data.open("zdekodowana_treść.txt", ios::out);

    if (!in_data.good()) {
        cout << "error[1]" << endl;
        return 0;
    }
    if(!out_data.good())
    {
        cout<<"error[2]";
        return 0;
    }

    struct_pomocznicze element;

    in_data >> element.poz;
    in_data >> element.licz_znak;
    in_data >> element.next_char;
   // cout << element.poz << " " << element.licz_znak << " " << element.next_char;

    for (int i = 0; i < size_slownik; i++) {
        slownik[i] = element.next_char;
    }
    cout<<slownik[size_slownik]<<endl;
    out_data << element.next_char;

    while (!in_data.eof()) {
        in_data >> element.poz >> element.licz_znak;
        if (in_data.eof()) {
            break;
        }
        char decode_LZ[size_slownik]={'\0'};
        in_data >> element.next_char;

        for (int i = 0; i < element.licz_znak; ++i) {
            decode_LZ[i] = slownik[element.poz + i];
        }
        decode_LZ[element.licz_znak] = element.next_char;
        decode_LZ[element.licz_znak + 1] = '\0';

        int a = 0;
        for (int i = 0; i < size_slownik - element.licz_znak - 1; i++) {
            slownik[i] = slownik[i + element.licz_znak + 1];
        }

        for (int i = size_slownik - element.licz_znak - 1; i < size_slownik; ++i) {
            slownik[i] = decode_LZ[a];
            a++;
        }

        out_data << decode_LZ;
    }


    in_data.close();
    out_data.close();
    return 0;
}