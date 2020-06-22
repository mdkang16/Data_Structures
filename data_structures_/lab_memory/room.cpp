/**
 * @file room.cpp
 */

#include <iostream>
#include "room.h"

using namespace std;

Room::Room()
    : capacity(0), count(0), max_letters(26), letterCount(0)
{
  letters = new Letter[max_letters];
}

Room::Room(const string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
  letters = new Letter[max_letters];
  copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    //cout<<"TEST ROOM"<<name<<"letterCount = "<<letterCount<<"letter0 addr"<<&letters[0]<<endl;
    letters[letterCount] = L;
    //cout<<"HIHIHI"<<endl;
    letterCount++;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print(std::ostream & stream /* = std::cout */)
{

    stream << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        stream << " " << letters[L].letter;
    stream << endl;
}

void Room::clear()
{
    if (letters != NULL)

        delete [] letters;
        letters=NULL;
}

void Room::copy(const Room& other)
{
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;

    if(letters==NULL)
    {
      letters = new Letter[max_letters];
    }

      for(int x=0; x<letterCount; x++)
      {
        letters[x]=other.letters[x];
      }
}
