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

int user::get_final_chance(int chance,int hours_passed,string name_of_possible_chance)
{
    int bonus = 0; // need to distract this bonus
    if(_type==_fixed){
        return chance;
    }
    else if(_type==_was_before_depend){

        // check story if was before
        for(const auto &i:story){
            if(i._bug==name_of_possible_chance){
                bonus ++;

            }
        }
        chance = chance-bonus;
        if (chance< 0){
            chance =0;
        }
        return chance;
    }
    else{
        // check hours passed if
        while(hours_passed-20>=0){
            bonus++;
        }
        chance = chance-bonus;
         if (chance< 0){
             chance =0;
          }
        return chance;
    }
}

bool user::randomise_appearence_of_a_bug(int chance)
{
    int appearence;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,10);
    appearence = dist(gen);
    if(appearence<=chance){
        return true;
    }
    else{
        return false;
    }

}

void user::working_on_program(vector<error> available_errors,int hours_passed)
{
    int temp_chance;
    // for each error
    for(const auto &i:available_errors){
        //scan if can appear in this program
        for(const auto &j:i.list_of_programs_and_chance_of_appearance_in_them){
            if(_current_program.first==j.first){
                temp_chance = get_final_chance(j.second,hours_passed,i.error_name()); // get_final_chance
                // randomise using chance
                if(randomise_appearence_of_a_bug(temp_chance)){ // if bug appeared
                    story.push_back(debugStory(i.error_name(),hours_passed)); // write it and the time of appearence in the story
                    bug_spotted=true;
                    current_bug_working_time_left=i.average_fixing_time();
                    return;
                }
            }
        }
    }
}

void user::create_time_of_usage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(current_program().second-2,current_program().second+2);
    _necessary_work_time = dist(gen);
}

void user::pick_up_random_program()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,program_and_average_time.size()-1);
    int choise = dist(gen);
    _current_program = program_and_average_time[choise];
}

pair<std::string, int> user::current_program() const
{
    return _current_program;
}

void user::Set_current_program(pair<string,int> program)
{
    _current_program = program;
}

bool user::occupied() const
{
    return _occupied;
}

void user::Set_occupied(bool occupied)
{
    _occupied = occupied;
}

int user::necessary_work_time() const
{
    return _necessary_work_time;
}

void user::Set_necessary_work_time(int time)
{
    _necessary_work_time = time;
}

void user::Set_time_of_fix(int time_of_fix)
{
    story.back()._time_of_fix = time_of_fix;
}

std::string user::name() const
{
    return _name;
}

user::user(std::vector<string> available_programs, string user_name)
{
   set_program_and_average_time(available_programs);
   _name = user_name;
   _occupied = false;
}

user::user()
{

}

user::user(const user &obj)
{
    bug_spotted=obj.bug_spotted;
    current_bug_working_time_left = obj.current_bug_working_time_left;
    _name = obj._name;
    _type = obj._type;
    story =  obj.story;
    _occupied = obj._occupied;
    _necessary_work_time= obj._necessary_work_time;
    program_and_average_time = obj.program_and_average_time;
}

user::debugStory::debugStory(string bug,int time_of_appearence)
{
    _bug=bug;
    _time_of_appearence=time_of_appearence;
    _time_of_fix = 0;
}
