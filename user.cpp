#include "user.h"

void user::generate_type_of_user()
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0,2);
    _type = static_cast<type_of_user>(dist(gen)); // generate time
}

void user::set_program_and_average_time(std::vector<string> available_programs)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_programs.begin(),available_programs.end(),gen);

    std::uniform_int_distribution<> dist(1,available_programs.size()); // choose new size

    int new_size = dist(gen);
    available_programs.erase(available_programs.begin() + new_size, available_programs.end()); // deleted extra

    for(const auto &i:available_programs){
        std::uniform_int_distribution<> dist(1,10); // average time of usage of program
        program_and_average_time.push_back(std::make_pair(i,dist(gen)));
    }

}
std::string user::name() const
{
    return _name;
}

user::user(std::vector<string> available_programs)
{
   set_program_and_average_time(available_programs);
}

user::debugStory::debugStory(string bug,int time_of_appearence,int time_of_fix)
{
    _bug=bug;
    _time_of_appearence=time_of_appearence;
    _time_of_fix=time_of_fix;
}
