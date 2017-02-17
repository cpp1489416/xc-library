#pragma once
#ifndef GAGENOME_H
#define GAGENOME_H

#include <vector>

namespace GA
{
    class Genome
    {
    public:
        typedef int Bit;
        static const Bit HAVE_BIT = 1;
        static const Bit NO_BIT = 0;

    public:
        Genome(int length);
        ~Genome();
        Genome(const Genome &genome) = default;
        Genome &operator = (const Genome &rhs) = default;
        const Bit &At(int index) const { return mArray[index]; }
        Bit &At(int index) { return mArray[index]; }
        int GetLength() const { return mArray.size(); }
        void SetLength(int length) { mArray.resize(length); }
        double GetFitness() const { return mFitness; }
        double GetFitness() { return mFitness; }
        double SetFitness(double fitness) { mFitness = fitness; }
        void RandomFill();
        
    private:
        std::vector<Bit> mArray;
        double mFitness;
    };
}

#endif // GAGENOME_H