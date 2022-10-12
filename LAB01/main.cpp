#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <complex>

using mojamapa_t = std::map<int, double>;
using mojafunkcja_t = std::function<double(mojamapa_t)>;

void wypisz(mojamapa_t mapa, const mojafunkcja_t& func){
    std:: cout << func(std::move(mapa)) << std::endl;
}

int main(int argc, char **argv) {
    using namespace std;
    map<int, double> mapa = {
            {0, 1}, // example
            {1, 2}
    };
    map<string, mojafunkcja_t> formatery;
    formatery["add"] = [](mojamapa_t add) {
        return add.at(2) + add.at(3);
    };
    formatery["sin"] = [](mojamapa_t si) {
        double result = si.at(2) * (numbers::pi/180);
        return sin(result) ;
    };
    formatery["mod"] = [](mojamapa_t mod) {
        return (int)mod.at(2) % (int)mod.at(3);
    };
    try {
        vector<string> argumenty(argv, argv + argc);
        for( int i=2; i < argumenty.size(); i++){
            mapa[i] = stoi(argumenty.at(i));
        }
        auto selected_f = argumenty.at(1);
        wypisz(mapa, formatery.at( selected_f));
    } catch (out_of_range out_of_range) {
        cout << "Jestem programem do liczenia sumy, sinusa i reszty z dzielenia";
        for (auto [k, v] : formatery) cout << " " << k;
        cout << endl;
    }
    return 0;
}