#include "zonemaps.h"
#include "tuple"
#include "iostream"
#include "vector"
#include <climits>

using namespace std;
template<typename T>
zonemap<T>::zonemap(std::vector<T> _elements, uint _num_elements_per_zone)
{
    // constructor 
    elements = _elements;
    num_zones = _elements.size()/_num_elements_per_zone;
    num_elements_per_zone = _num_elements_per_zone;
    build();
}

template<typename T>
void zonemap<T>::build() {
    int cnt = 0;
    int _min = INT_MAX, _max = INT_MIN;
    vector<T> cur_zone;
    for (T e : elements) {
        _min = std::min(_min, e);
        _max = std::max(_max, e);
        cur_zone.push_back(e);
        cnt++;

        if (cnt == num_elements_per_zone) {
            zone<T> new_zone;
            new_zone.min = _min;
            new_zone.max = _max;
            new_zone.size = cnt;
            new_zone.elements = cur_zone;
            zones.push_back(new_zone);

            cur_zone.clear();
            cnt = 0;
            _min = INT_MAX;
            _max = INT_MIN;
        }
    }
    if (cnt != 0) {
        zone<T> new_zone;
        new_zone.min = _min;
        new_zone.max = _max;
        new_zone.size = cnt;
        new_zone.elements = cur_zone;
        cur_zone.clear();
        zones.push_back(new_zone);
    }
}


template<typename T>
size_t zonemap<T>::query(T key)
{
    int cnt = 0;
    for (zone<T> zone : zones) {
        if (zone.min <= key <= zone.max) {
            for (T e : zone.elements) {
                if (e == key) 
                    cnt++;
            }
        }
    }
    return cnt;
}

template<typename T>
std::vector<T> zonemap<T>::query(T low, T high) {

}

