#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Day of Month in Haab:
// Starts from  0
// End of       19,     if Month != uayet
//              4,      if Month == uayet
// Days in Year: 20 * 18 + 5 == 365
// Format (the first day, as example): 0. pop 0
const size_t NumOFMonthINHaab = 19;
const char HaabMonthNames[NumOFMonthINHaab][7] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen",
                "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
const int DaysINYearHaab = 365;
const int DaysINMonthHaab = 20;
// Day in Tzolkin:
// Two systems:
//  - Number: From 1 to 13, loop (length 13)
//  - Sign:   From imix to ahau, loop (length 20)
// Days in Year: 13 * 20 == 260
// Format (the first day, as example): 1 imix 0
const size_t NumOFGroupINTzolkin = 20;
const char TzolkinDayNames[NumOFGroupINTzolkin][9] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik",
                "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab",
                "canac", "ahau"};
const int DaysINYearTzolkin = 260;
const int NumOFLoop = 13;

int main () {
    std::ios_base::sync_with_stdio(false);
    size_t limit(0);
    cin >> limit;
    cin.ignore();
    cout << limit << endl;
    size_t cnt(0);

    string buffer;
    bool parseHaabDate (string& input, int& day, char month[], int& year);
    int getDaysSinceGenesisFromHaab (const int& day, const char month[], const int& year);
    bool getDateFromDaysCountForTzolkin (int days, int& day, size_t& group_idx, int& year);
    while (getline(cin, buffer) and cnt < limit) {
        ++cnt;
        int day(0), year(0);
        char month[7];
        if (parseHaabDate(buffer, day, month, year)) {
            int days_since_genesis(getDaysSinceGenesisFromHaab(day, month, year));
            if (!(days_since_genesis < 0)) {
                int res_day(0), res_year(0);
                size_t res_group_idx(0);
                if (getDateFromDaysCountForTzolkin(days_since_genesis, res_day, res_group_idx, res_year)) {
                    cout << res_day << " " << TzolkinDayNames[res_group_idx] << " " << res_year << endl;
                } else {
                    // cout << "getDateFromDaysCountForTzolkin failed" << endl;
                }
            } else {
                // cout << "days_since_genesis < 0" << endl;
            }
        } else {
            // cout << "parseHaabDate failed" << endl;
        }
    }
    return 0;
}

bool parseHaabDate (string& input, int& day, char month[], int& year) {
    if (input.empty()) {
        return false;
    }
    size_t found = input.find_first_of('.');
    if (found == std::string::npos or found == input.size() - 1) {
        return false;
    }
    day   = atoi(input.substr(0, found).c_str());
    input = input.substr(found + 1, std::string::npos);
    input.erase(0, min(input.find_first_not_of(' '), input.size() - 1));
    found = input.find_first_of(' ');
    if (found == std::string::npos or found == input.size() - 1) {
        return false;
    }
    strcpy(month, input.substr(0, found).c_str());
    year  = atoi(input.substr(found + 1, std::string::npos).c_str());
    return true;
}

int getDaysSinceGenesisFromHaab (const int& day, const char month[], const int& year) {
    if (day < 0 or year < 0) {
        return -1;
    }
    size_t c_month(-1);
    for (size_t i = 0; i != NumOFMonthINHaab; ++i) {
        if (0 == strcmp(month, HaabMonthNames[i])) {
            c_month = i;
            break;
        }
    }
    if (-1 == c_month) {
        return -2;
    } else if (NumOFMonthINHaab - 1 == c_month and day > 4) {
        return -3;
    }
    return year * DaysINYearHaab + c_month * DaysINMonthHaab + day;
}

bool getDateFromDaysCountForTzolkin (int days, int& day, size_t& group_idx, int& year) {
    if (days < 0) {
        return false;
    }
    year = days / DaysINYearTzolkin;
    days %= DaysINYearTzolkin;
    day = days % NumOFLoop + 1;
    group_idx = days % NumOFGroupINTzolkin;
    return true;
}

