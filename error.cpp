#include "error.h"

int error::generate_average_fixing_time()
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(1,4);
    return dist(gen); // generate time
}

int error::generate_appearence_chance()
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,10);
    return dist(gen);
}

void error::match_pairs(std::vector<std::string> available_programs)
{
    for(const auto &i:available_programs){
        std::string temp = i;
        list_of_programs_and_chance_of_appearance_in_them.push_back(
                std::make_pair(i,generate_appearence_chance()));
    }
}

std::string error::error_type()
{
    return _error_type;
}

int error::average_fixing_time()
{
    return _average_fixing_time;
}

error::error(std::string error_type,std::vector<std::string> available_programs )
{
    _error_type=error_type;
    _average_fixing_time = generate_average_fixing_time();
    match_pairs(available_programs);
}
