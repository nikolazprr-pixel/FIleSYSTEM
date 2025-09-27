#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem> 
using namespace std;
namespace fs = std::filesystem;
//я сделал чтоб 2 файла сами создавались а не были на комее 
// таблицы 
map<string, string> rusToLat = {
    {"А","A"},{"Б","B"},{"В","V"},{"Г","G"},{"Д","D"},{"Е","E"},{"Ё","Yo"},
    {"Ж","Zh"},{"З","Z"},{"И","I"},{"Й","Y"},{"К","K"},{"Л","L"},{"М","M"},
    {"Н","N"},{"О","O"},{"П","P"},{"Р","R"},{"С","S"},{"Т","T"},{"У","U"},
    {"Ф","F"},{"Х","Kh"},{"Ц","Ts"},{"Ч","Ch"},{"Ш","Sh"},{"Щ","Sch"},
    {"Ы","Y"},{"Э","E"},{"Ю","Yu"},{"Я","Ya"},
    {"а","a"},{"б","b"},{"в","v"},{"г","g"},{"д","d"},{"е","e"},{"ё","yo"},
    {"ж","zh"},{"з","z"},{"и","i"},{"й","y"},{"к","k"},{"л","l"},{"м","m"},
    {"н","n"},{"о","o"},{"п","p"},{"р","r"},{"с","s"},{"т","t"},{"у","u"},
    {"ф","f"},{"х","kh"},{"ц","ts"},{"ч","ch"},{"ш","sh"},{"щ","sch"},
    {"ы","y"},{"э","e"},{"ю","yu"},{"я","ya"}
};

map<string, string> latToRus = {
    {"Yo","Ё"},{"Zh","Ж"},{"Kh","Х"},{"Ts","Ц"},{"Ch","Ч"},{"Sh","Ш"},{"Sch","Щ"},
    {"Yu","Ю"},{"Ya","Я"},
    {"yo","ё"},{"zh","ж"},{"kh","х"},{"ts","ц"},{"ch","ч"},{"sh","ш"},{"sch","щ"},
    {"yu","ю"},{"ya","я"},
    {"A","А"},{"B","Б"},{"V","В"},{"G","Г"},{"D","Д"},{"E","Е"},{"Z","З"},{"I","И"},{"Y","Й"},{"K","К"},
    {"L","Л"},{"M","М"},{"N","Н"},{"O","О"},{"P","П"},{"R","Р"},{"S","С"},{"T","Т"},{"U","У"},{"F","Ф"},
    {"a","а"},{"b","б"},{"v","в"},{"g","г"},{"d","д"},{"e","е"},{"z","з"},{"i","и"},{"y","й"},{"k","к"},
    {"l","л"},{"m","м"},{"n","н"},{"o","о"},{"p","п"},{"r","р"},{"s","с"},{"t","т"},{"u","у"},{"f","ф"}
};

// ну функция для рус->лат
string f1(const string &txt) {
    string reslt;
    size_t j = 0; 
    while (j < txt.size()) {
        string ch(1, txt[j]);
        if ((unsigned char)txt[j] >= 0xD0) { // кириллица?
            if (j+1 < txt.size()) {
                ch += txt[j+1];
                j += 2;
            } else { j++; }
        } else j++;
        if (rusToLat.count(ch)) reslt += rusToLat[ch];
        else reslt += ch;
        //cout << "DEBUG: " << ch << endl; // проверял тут
    }
    return reslt;
}

// лат->рус
string f2(string txt) {
    string res; 
    int zz = 0;
    while (zz < (int)txt.size()) {
        bool ok = false;
        if (zz+1 < (int)txt.size()) {
            string t2 = txt.substr(zz,2);
            if (latToRus.count(t2)) {
                res += latToRus[t2];
                zz += 2;
                ok = true;
            }
        }
        if (!ok) {
            string t1 = txt.substr(zz,1);
            if (latToRus.count(t1)) res += latToRus[t1];
            else res += t1;
            zz++;
        }
        //cout << "DEBUG i=" << zz << endl; // отладка была
    }
    return res;
}

int main() {
    setlocale(LC_ALL,""); // вроде надо для кириллицы

    // проверка на input.txt
    if (!fs::exists("input.txt")) {
        ofstream ff("input.txt");
        ff << "Пример текста для транслітерації\n";  // чтоб не пустой был
        ff.close();
        cout << "input.txt создался. Впишите туда текст и перезапустите!!\n";
        return 0; // пока выходим
    }

    int choise = 0;
    cout << "Выберите направление:\n";
    cout << "1 - Рус->Англ\n";
    cout << "2 - Англ->Рус\n";
    cout << "Ваш выбор: ";
    cin >> choise;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "Не смог открыть input.txt\n";
        return 1; // ну выходим
    }
    if (!fout.is_open()) {
        cout << "Не смог открыть output.txt\n";
        return 2; // странно, но вдруг
    }

    string line, final_line, tmp_line;
    while (getline(fin, line)) {
        
        if (choise==1) {
            tmp_line = f1(line);
            final_line = tmp_line; // лишняя переменная но ладно
        } else {
            final_line = f2(line);
        }
        fout << final_line << "\n";
    }

    cout << "Готово! Смотри output.txt\n";
    //system("pause"); // раньше стояло, убрал
    return 0;
}
