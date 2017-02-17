#include "GAGeceticFinder.h"

namespace GA
{
    GeneticFinder::GeneticFinder() :
        mMap(100, 100), mBestMap(100, 100)
    {
    }

    GeneticFinder::~GeneticFinder()
    {
    }

    void GeneticFinder::Timeout()
    {
    }

    void GeneticFinder::Epoch()
    {
    }

    void GeneticFinder::Mutate(Genome & genome)
    {
        for (int i = 0; i < genome.GetLength(); i++)
        {
            bool need = (rand() % 100) < (int)(mMutationRate * 100);
            if (need)
            {
                genome.At(i) = !genome.At(i);
            }
        }
    }

    void GeneticFinder::Crossover(const Genome & mother, const Genome & father, Genome & child1, Genome & child2)
    {
        child1.SetLength(mGenomeLength);
        child2.SetLength(mGenomeLength);
        int pos = rand() % mGenomeLength;

        for (int i = 0; i <= pos; i++)
        {
            child1.At(i) = mother.At(i);
            child2.At(i) = father.At(i);
        }

        for (int i = pos + 1; i < mGenomeLength; i++)
        {
            child1.At(i) = father.At(i);
            child2.At(i) = mother.At(i);
        }
    }

    Genome & GeneticFinder::RouletteWheelSelect()
    {
        double all = 0.0;
        for (int i = 0; i < mPopulationSize; i++)
        {
            all += mGenomes[i].GetFitness();
        }

        double target = RandomFloat() * all;
        double cur = 0.0;
        for (int i = 0; i < mPopulationSize; i++)
        {
            cur += mGenomes[i].GetFitness();
            if (cur >= target)
            {
                return mGenomes[i];
            }
        }
    }

    void GeneticFinder::UpdateFitnessScores()
    {
    }

    std::vector<Map::Direction> GeneticFinder::Decode(const Genome &genome) const 
    {
        std::vector<Direction> ans;
        for (int i = 0; i < genome.GetLength(); i += 2)
        {
            std::vector<Genome::Bit> tmp;
            tmp.push_back(genome.At(i));
            tmp.push_back(genome.At(i + 1));
            ans.push_back(ArrayToDirection(tmp));
        }

        return ans;
    }

    void GeneticFinder::CreateStartPopulation()
    {
        mGenomes.clear();
        for (int i = 0; i < mPopulationSize; i++)
        {
            mGenomes.push_back(Genome(mGenomeLength));
        }
    }

    GeneticFinder::Direction GeneticFinder::ArrayToDirection(const std::vector<Genome::Bit>& array)
    {
        if (array[0] == Genome::NO_BIT)
        {
            if (array[1] == Genome::NO_BIT)
            {
                return Direction::LEFT;
            }
            else
            {
                return Direction::DOWN;
            }
        }
        else
        {
            if (array[1] == Genome::NO_BIT)
            {
                return Direction::RIGHT;
            }
            else
            {
                return Direction::UP;
            }
        }
    }

    double GeneticFinder::RandomFloat()
    {
        return (double)rand() / (double)RAND_MAX;
    }
}
