#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <complex>

using mojamapa_t = std::map<std::string, int>;
using mojafunkcja_t = std::function<double(mojamapa_t)>;

void wypisz(mojamapa_t mapa, const mojafunkcja_t& func){
    std:: cout << func(std::move(mapa)) << std::endl;
}

int main(int argc, char **argv) {
    using namespace std;
    map<string, int> mapa = {
            {"arg_0", 1}, // example
            {"arg_1", 2}
    };
    map<string, mojafunkcja_t> formatery;
    formatery["add"] = [](mojamapa_t add) {
        return add.at("arg_2") + add.at("arg_3");
    };
    formatery["sin"] = [](mojamapa_t si) {
        double result = si.at("arg_2") * (numbers::pi/180);
        return sin(result) ;
    };
    formatery["mod"] = [](mojamapa_t mod) {
        return mod.at("arg_2") % mod.at("arg_3");
    };
    try {
        vector<string> argumenty(argv, argv + argc);
        for( int i=2; i < argumenty.size(); i++){
            mapa.insert({{"arg_" + to_string(i), stoi(argumenty.at(i))}});
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