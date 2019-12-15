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
//    std::shuffle(available_programs.begin(),available_programs.end(),gen);

//    std::uniform_int_distribution<> dist(1,available_programs.size()); // choose new size

//    int new_size = dist(gen);
//    available_programs.erase(available_programs.begin() + new_size, available_programs.end()); // deleted extra


    for(const auto &i:available_programs){
        std::uniform_int_distribution<> dist(1,10); // average time of usage of program
        program_and_average_time.push_back(std::make_pair(i,dist(gen)));
    }
}

int user::necessary_work_time()
{
    return _necessary_work_time;
}

void user::Set_necessary_work_time(int time)
{
    _necessary_work_time = time;
}

std::string user::name() const
{
    return _name;
}

user::user(std::vector<string> available_programs, string user_name)
{
   set_program_and_average_time(available_programs);
   _name = user_name;
}

user::user()
{

}

user::user(const user &obj)
{
    _name = obj._name;
    _type = obj._type;
    story =  obj.story;
    program_and_average_time = obj.program_and_average_time;
}

user::debugStory::debugStory(string bug,int time_of_appearence,int time_of_fix)
{
    _bug=bug;
    _time_of_appearence=time_of_appearence;
    _time_of_fix=time_of_fix;
}
