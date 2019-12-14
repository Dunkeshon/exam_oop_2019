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

void error::match_pairs(vector<string> available_programs)
{
    for(const auto &i:available_programs){
        string temp = i;
        list_of_programs_and_chance_of_appearance_in_them.push_back(
                std::make_pair(i,generate_appearence_chance()));
    }
}

string error::error_name() const
{
    return _error_name;
}

int error::average_fixing_time() const
{
    return _average_fixing_time;
}

error::error(string error_type,vector<string> available_programs )
{
    _error_name=error_type;
    _average_fixing_time = generate_average_fixing_time();
    match_pairs(available_programs);
}

error error::operator =(error other)
{
    _average_fixing_time = other._average_fixing_time;
    _error_name = other._error_name;
    list_of_programs_and_chance_of_appearance_in_them = other.list_of_programs_and_chance_of_appearance_in_them;
    return *this;
}
