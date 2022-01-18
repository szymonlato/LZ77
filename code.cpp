#include <iostream>
#include <fstream>

using namespace std;

int sieze_buff, size_slownik, last_poz_buff;
char *buff, *slownik;

struct struct_pomocnicze {
    int poz, licz_znak;
    char next_char;
};

struct_pomocnicze szukaj_slowa() {
    struct_pomocnicze tmp, tmp1;
    tmp.licz_znak = tmp1.licz_znak = 0;
    tmp.poz = tmp1.poz = 0;
    int a = 1;
    for (int i = 0; i < sieze_buff; i++) {
        int w = a = 1;
        for (int poz = 0; poz < size_slownik; poz++) {
            a = 1;
            for (int j = 0; j < i; j++) {
                if (buff[j] != slownik[poz + j])
                    a = 0;
            }
            if (a == 1) {
                tmp1.poz = poz;
                tmp1.licz_znak = i;
                w = 0;
                if (tmp1.licz_znak > tmp.licz_znak) {
                    tmp.licz_znak = tmp1.licz_znak;
                    tmp.poz = tmp1.poz;
                }
                break;
            }
        }
        if (w == 1) break;
    }

    if (tmp.licz_znak >= last_poz_buff) {
        tmp.licz_znak = last_poz_buff - 1;
    }
    tmp.next_char = buff[tmp.licz_znak];
    return tmp;
}

void moveWindow(int mov, fstream *inputFile, struct_pomocnicze element) {
    for (int i = 0; i < size_slownik - mov; ++i) {
        slownik[i] = slownik[i + mov];
    }
    int j = 0;
    for (int i = size_slownik - mov; i < size_slownik; ++i) {
        slownik[i] = buff[j];
        j++;
    }

    for (int i = 0; i < sieze_buff - mov; ++i) {
        buff[i] = buff[i + mov];
    }
    for (int i = sieze_buff - mov; i < sieze_buff; ++i) {
        if (inputFile->eof()) {
            last_poz_buff--;
            buff[i] = ' ';
        } else {
            *inputFile >> buff[i];
            if (inputFile->eof()) {
                last_poz_buff--;
                buff[i] = '\0';
            }
        }
    }
}


int main() {
    cout << "Podaj dlugosc bufora :";
    cin >> sieze_buff;
    cout<<endl;
    cout<<"Podaj dlugosc slownika:";
    cin>> size_slownik;
    last_poz_buff = sieze_buff;
    buff = new char[sieze_buff + 1];
    buff[sieze_buff] = {'\0'};
    slownik = new char[size_slownik + 1];
    slownik[size_slownik] = {'\0'};
    fstream in_data, out_data;
    in_data.open("wejście.txt", ios::in);
    out_data.open("wyjście_zakodowane.txt", ios::out);

    if (!in_data.good()) {
        cout << "error[1]" << endl;
        return 0;
    }
    if(!out_data.good())
    {
        cout<<"error[2]";
        return 0;
    }

    struct_pomocnicze element{};
    char c;
    in_data >> c;
    element.poz = 0;
    element.licz_znak = 0;
    element.next_char = c;
    out_data << element.poz << " " << element.licz_znak << " " << element.next_char;

    for (int i = 0; i < size_slownik; ++i) {
        slownik[i] = c;
    }
    for (int i = 0; i < sieze_buff; ++i) {
        in_data >> buff[i];
        if (in_data.eof()) {
            last_poz_buff--;
        }
    }

    int mov;
    while (last_poz_buff > 0) {
        element = szukaj_slowa();
        out_data << endl << element.poz << " " << element.licz_znak << " " << element.next_char;
        mov = element.licz_znak + 1;
        moveWindow(mov, &in_data, element);
    }
    in_data.seekg(0,ios::end);
    out_data.seekg(0,ios::end);
    float t = in_data.tellg();
    float y = out_data.tellg();
    float Kompresja = t/y;
    cout<<Kompresja;


    in_data.close();
    out_data.close();
    delete buff;
    delete slownik;
    return 0;
}