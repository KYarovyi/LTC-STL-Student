#pragma once
#include "bar_serving.h"
#include <functional>
#include <array>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */

struct BeerOrganizer
{
public:
    BeerBrand operator()()
    {
        if (it == Brands.end())
            it = Brands.begin();
        it++;
        return *it;
    }
private:
    std::array<BeerBrand, 8> Brands;
    std::array<BeerBrand, 8>::iterator it = Brands.begin();
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand bear)
{
    if (bear == BeerBrand::Corona || bear == BeerBrand::HoeGaarden)
        return false;
    return true;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand lhs,BeerBrand rhs)
{
     return static_cast<bool>(getBeerCountry(lhs) == getBeerCountry(rhs));
};

struct MixingPolicy
{
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix(AlcoholDrink alcohol, NonAlcoholDrink non_alcohol)
    {
        Cocktail currentCocktail = Cocktail::Oops;
        if(alcohol == AlcoholDrink::Gin && non_alcohol == NonAlcoholDrink::LimeJuice)
            currentCocktail = Cocktail::Gimlet;
        if(alcohol == AlcoholDrink::Gin && non_alcohol == NonAlcoholDrink::GrapefruitJuice)
            currentCocktail = Cocktail::Greyhount;
        if(alcohol == AlcoholDrink::Whiskey && non_alcohol == NonAlcoholDrink::SevenUp)
            currentCocktail = Cocktail::SevenPlusSeven;
        return currentCocktail;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};
