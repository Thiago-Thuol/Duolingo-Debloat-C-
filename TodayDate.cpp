#ifndef TODAY_DATE_CPP
#define TODAY_DATE_CPP

#include "TodayDate.hpp"

string TodayDate(){
    time_t now = time(nullptr);

    tm local{};
    localtime_r(&now, &local);

    ostringstream ss;
    ss << put_time(&local ,"%Y-%m-%d");
    return ss.str();
}

int StreakCheck(string s){
    string ss = TodayDate();
    time_t antiga , hoje;

    //convert the string to the time_t struct to be able to use the difftime function
    if (!PegaTempo(s , antiga) || !PegaTempo(ss , hoje)) return false;
    
    int dias = lround (difftime(hoje, antiga) /86400.0); // seconds that a day have

    return dias;
    
}

bool PegaTempo( string& d, time_t& saida){
    tm t {};

    //define some paramether to tm work propely
    t.tm_hour = 12;
    t.tm_isdst = -1;

    istringstream in (d);

    //check if in fails
    if (in.fail()) return false;

    //pass to the addres of t the time of in using get_time function in year-mounth-day tipe
    in >> get_time(&t, "%Y-%m-%d");

    saida = mktime(&t);
    return true;
}


#endif