#include "card.h"
Card::Card()
{
    qsrand(QTime::currentTime().msec());
}
Card::~Card(){
}
int Card::getrandom(int start, int end){
    return qrand() % (end - start + 1) + start;
}
