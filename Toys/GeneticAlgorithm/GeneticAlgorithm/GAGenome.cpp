#include "GAGenome.h"
#include <cstdlib>

namespace GA
{
    Genome::Genome(int length) : mFitness(0.0)
    {
        SetLength(length);
        RandomFill();
    }

    Genome::~Genome()
    {
    }

    void Genome::RandomFill()
    {
        for (int i = 0; i < mArray.size(); i++)
        {
            mArray[i] = std::rand() % 2;
        }
    }
}

