#pragma once

#ifndef GAGENETICALGORITHM_H
#define GAGENETICALGORITHM_H

#include <vector>
#include "GAMap.h"
#include "GAGenome.h"

namespace GA
{
    class GeneticFinder
    {
    public:
        typedef Map::Direction Direction;

    public:
        GeneticFinder();
        ~GeneticFinder();
        GeneticFinder(const GeneticFinder &) = delete;
        GeneticFinder &operator = (const GeneticFinder &) = delete;
        const Map &GetMap() const { return mMap; }
        void SetMap(const Map &map) { mMap = map; }
        int &ReferPopulationSize() { return mPopulationSize; }
        double &ReferCrossoverRate() { return mCrossoverRate; }
        double &ReferMutationRate() { return mMutationRate; }
        void Timeout();
        void Epoch();
       
    private:
        void Mutate(Genome &genome);
        void Crossover(const Genome &mother, const Genome &father, Genome &child1, Genome &child2);
        Genome &RouletteWheelSelect();
        void UpdateFitnessScores();
        std::vector<Map::Direction> Decode(const Genome &genome) const;
        void CreateStartPopulation();
        static Direction ArrayToDirection(const std::vector<Genome::Bit> &array);
        static double RandomFloat();

    private:
        std::vector<Genome> mGenomes;
        int mPopulationSize;
        double mCrossoverRate;
        double mMutationRate;
        int mGenomeLength; // how many bits in each chromo, it is also the name of grnome   
        int mGeneLength; // how many bits in each JI YIN. it is 2 becase 4 bit represent a location 
        Genome *mFittestGenome = nullptr;
        double mBestFitnessScore = 0.0;
        double mTotalFitnessScore = 0.0;
        int mGeneration = 0;
        Map mMap;
        Map mBestMap; // this map is used for rending
        bool mBusy = false; // true if it is still running
    };
}

#endif // GAGENETICALGORITHM_H