#include <iostream>
#include "llist.h"


using namespace std;

void dump(const LList& l)
{
	for(size_t i = 0; i < l.size(); ++i, cout << " ") cout << l[i];
}

int main()
{
    LList l;
    LList tmp;
    for (int i = 0; i < 20000; ++i) {
        tmp.push_back(i);
    }
    //Если отсутствуют move-конструкторы, сработают
    //обычные конструкторы копирования
    l = std::move(tmp);
    //При MOVE_ENABLE=1 пик потребления памяти - ~540KB
    //При MOVE_ENABLE=0 пик потребления памяти - ~980KB
	return 0;
}
