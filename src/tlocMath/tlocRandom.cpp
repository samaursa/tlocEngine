//*** Random.cpp ***

#include "tlocRandom.h"

//*** Constructor ***

Random::Random():
index_(0)
{
  Seed(0x5ee39c34);
}


//*** Seed ***

void Random::Seed(unsigned int s)
{	
  state_[0]=s^0xf68a9fc1;
  for (int i=1; i<16; i++) 
  {
    state_[i] = (0x6c078965U * (state_[i-1] ^ (state_[i-1] >> 30)) + i); 
  }
}


//*** SetState ***

void Random::SetState(const unsigned int state[16], int index)
{
  for (int i=0; i<16; i++)
  {
    state_[i]=state[i];
  }

  index_=index&15;
}


//*** GetState ***

void Random::GetState(unsigned int state[16], int& index)
{
  for (int i=0; i<16; i++)
  {
    state[i]=state_[i];
  }

  index=index_;
}


//*** RandomInteger ***

unsigned int Random::RandomInteger()
{
  unsigned int a = state_[index_];
  unsigned int c = state_[(index_+13)&15];
  unsigned int b = a^c^(a<<16)^(c<<15);
  c = state_[(index_+9)&15];
  c ^= (c>>11);
  a = state_[index_] = b^c;
  unsigned int d = a^((a<<5)&0xda442d20U);
  index_ = (index_ + 15)&15;
  a = state_[index_];
  state_[index_] = a^b^d^(a<<2)^(b<<18)^(c<<28);
  return state_[index_];
}


//*** RandomRanged ***

int Random::RandomRanged(int min, int max)
{
  int range=(max-min)+1;
  if (range<=0)
  {
    return min;
  }
  int value=(int)(RandomFloat()*range);
  return min+value; 
}


//*** RandomFloat ***

float Random::RandomFloat()
{
  // Get a random integer, and divide by 2^32
  return (RandomInteger()/4294967296.0f);     
}