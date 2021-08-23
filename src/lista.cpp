#include "lista.h"
#include <iostream>

Lista::Lista(int v, int dist)
    : v_(v)
    , dist_(dist)
    , prox_(nullptr)
{
}

Lista::~Lista()
{
}
