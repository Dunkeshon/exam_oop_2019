#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
#include <random>

using std::vector;
using std::string;
using std::pair;
/*
 * class to display an error that can appear during the program
 * _average_fixing_time - Average time to fix errors ; creates in constructor
 * error_type - Receiving by a param of a constructor
 * possibility of appearence an error
 */
class error
{
private:
    int _average_fixing_time;
    string _error_name;
    int generate_average_fixing_time();
    /*
     * return appearence_chance
     * details: The bigger is a number, the more is a chance of appearence (because we will calculate
     * it like this : if( *generated_number* <= appearence_chance){ spawn error }) ;
     * genereted number must be from 1 to 10
     */
    int generate_appearence_chance();
    /*
     * brief generate possibility of error for each technology (can be 0 )
     * param available_programs - programs,
     */
    void match_pairs(std::vector<std::string> available_programs);


public:

    vector<pair<string,int>> list_of_programs_and_chance_of_appearance_in_them;

    string error_name() const;

    int average_fixing_time() const;

    /*
     * constructor,
     * _average_fixing_time - Average time to fix errors ; creates in constructor
     * error_type - Receiving by a param of a constructor
     * possibility of appearence an error
     */
    error(string error_name,vector<string> available_programs);
    // КОНСТРУКТОР КОПИРОВАНИЯ

    /*
     * now it's not needed, maybe i'll get rid of it latter
     */
    error operator =(error other);
};
#endif // ERROR_H
