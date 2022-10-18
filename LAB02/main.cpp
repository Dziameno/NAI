#include <iostream>
#include <functional>
#include <random>

/**
 * domain - generate random domain points
 */

auto random_probe = [](auto f, auto domain, int itr) {
    auto current_p = domain();
    auto best_point = current_p;
    try {

        for (int i = 0; i < itr; i++) {
            if (f(current_p) < f(best_point)) {
                best_point = current_p;
            }
            current_p = domain();
        }

    } catch (std::exception &e) {
    }
    return best_point;
};

std::random_device rd;
std::mt19937 mt_generator(rd());

int main() {
    using namespace std;

    auto xy_generator = [&]() {
        std::uniform_real_distribution<> dis(-10, 10);
        return std::pair<double, double>(dis(mt_generator), dis(mt_generator));
    };

    auto sphere_f = [](pair<double, double> sphere) {
        return pow(sphere.first, 2) + pow(sphere.second, 2);
    };

    auto three_hump_camel_f = [](pair<double, double> three_hump_camel) {
        return 2*pow(three_hump_camel.first, 2) -
        1.05*pow(three_hump_camel.first, 4) +
        pow(three_hump_camel.first,6) / 6 +
        (three_hump_camel.first * three_hump_camel.second) +
        pow(three_hump_camel.second,2);
    };

    auto matyas_f = [](pair<double, double> matyas) {
        return 0.26 * (pow(matyas.first, 2) +
        pow(matyas.second, 2)) -
        0.48 * (matyas.first * matyas.second);
    };

    auto booth_f = [](pair<double, double> booth){
        return pow(booth.first+2*booth.second-7,2) +
        pow(2*booth.first+booth.second-5,2);
    };


    auto best_point = random_probe(sphere_f, xy_generator, 100);
    cout << "best sphere domain x = " << best_point.first << " y = " << best_point.second << endl;

    best_point = random_probe(three_hump_camel_f, xy_generator, 100);
    cout << "best three hump camel domain x = " << best_point.first << " y = " << best_point.second << endl;

    best_point = random_probe(matyas_f, xy_generator, 100);
    cout << "best matyas domain x = " << best_point.first << " y = " << best_point.second << endl;

    best_point = random_probe(booth_f, xy_generator, 100);
    cout << "best booth domain x = " << best_point.first << " y = " << best_point.second << endl;
    return 0;
}