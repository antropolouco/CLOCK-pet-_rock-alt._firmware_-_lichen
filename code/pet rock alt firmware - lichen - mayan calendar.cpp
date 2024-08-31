/// wofl's mayan calendar alt firmware for pet rock part 1

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class MayanCalendarCounter {
public:
    MayanCalendarCounter(int baktun = 13, int katun = 0, int tun = 11, int uinal = 14, int kin = 15) {
        // Mayan periods in days (1, 20, 365, 260, 400, 20800, 270000, 1352000, 57600000)
        periods = {1, 20, 365, 260, 400, 20800, 270400, 1352000, 57600000};
        // Initialize the Mayan date
        date = {kin, uinal, tun, katun, baktun};
        // Nahuales (Kin names) and Uinal names
        nahuales = {"Imix", "Ik’", "Ak’bal", "K’an", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "K’ib", "Kaban", "Etznab", "Kauak", "Ajau"};
        uinals = {"Pop", "Uo’", "Zip", "Sots", "Tsek", "Xul", "Yaxkin", "Mol", "Ch’en", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "K’ayab", "Kumk’u", "Uayeb"};
    }

    void increment(int days = 1) {
        date[0] += days;
        // Handle carry-over for the calendar periods
        for (size_t i = 0; i < periods.size(); ++i) {
            if (date[i] >= periods[i]) {
                if (i < periods.size() - 1) {
                    // Carry over to the next period
                    date[i + 1] += date[i] / periods[i];
                    date[i] %= periods[i];
                } else {
                    // If at the highest period, wrap around (overflow)
                    date[i] %= periods[i];
                }
            } else {
                break;  // No need to carry over if the current period is within its range
            }
        }
    }

    void adjust_to_start() {
        // Calculate the total number of days from the Mayan epoch (0.0.0.0.0.0) to the given date
        long long total_days =
            date[8] * 57600000 +  // Baktun * 57600000 days
            date[7] * 1352000 +   // Long Count * 1352000 days
            date[6] * 270400 +    // Baktun * 270400
            date[5] * 20800 +     // Baktun * 20800 days
            date[4] * 400 +       // Katun 400 days
            date[3] * 260 +       // Tun 260 days
            date[2] * 365 +       // Tzolk'in * 365 days
            date[1] * 20 +        // Uinal 18 * 20 + 5 Wayeb
            date[0];              // Kin * 1 day

        // Adjust the Kin (days) and Uinal (months in Haab')
        if (date[0] >= 20) {  // 20 K'in in a Uinal
            date[1] += date[0] / 20;
            date[0] %= 20;
        }

        // Adjust Uinal (18 Uinals of 20 days + 5 Wayeb days)
        if (date[1] >= ((18 * 20) + 5) / 20) {
            date[2] += date[1] / (((18 * 20) + 5) / 20);
            date[1] %= (((18 * 20) + 5) / 20);
        }

        // Adjust the Tzolk'in (13 day numbers cycling through 20 day names)
        if (date[2] >= 13) {
            date[3] += date[2] / 13;
            date[2] %= 13;
        }

        // Adjust the Tun (20 Uinals)
        if (date[3] >= 20) {
            date[4] += date[3] / 20;
            date[3] %= 20;
        }

        // Adjust the Katun (20 Tuns)
        if (date[4] >= 20) {
            date[5] += date[4] / 20;
            date[4] %= 20;
        }

        // Adjust the Baktun (52 Katuns)
        if (date[5] >= 52) {
            date[6] += date[5] / 52;
            date[5] %= 52;
        }

        // Adjust the Long Count (13 Baktun)
        if (date[6] >= 13) {
            date[7] += date[6] / 13;
            date[6] %= 13;
        }

        // Adjust the Precession period (5 Long Counts)
        if (date[7] >= 5) {
            date[8] += date[7] / 5;
            date[7] %= 5;
        }

        // Determine the position within the Tzolk'in cycle (260 days)
        int tzolkin_position = total_days % 260;

        // Determine the position within the Haab' cycle (365 days)
        int haab_position = total_days % 365;

        // Set Tzolk'in to 1 Ben
        int target_tzolkin_day_number = 1;
        std::string target_tzolkin_day_name = "Ben";
        int target_tzolkin_position = (std::find(nahuales.begin(), nahuales.end(), target_tzolkin_day_name) - nahuales.begin() + (target_tzolkin_day_number - 1)) % 260;

        // Adjust the Tzolk'in offset to start from 1 Ben
        date[0] = (target_tzolkin_position - tzolkin_position) % 260;

        // Set Haab' to 3 Zip
        int target_haab_day_number = 3;
        std::string target_haab_month_name = "Zip";
        int target_haab_position = (std::find(uinals.begin(), uinals.end(), target_haab_month_name) - uinals.begin()) * 20 + (target_haab_day_number - 1) % 365;

        // Adjust the Haab' offset to start from 3 Zip
        int haab_correction = (target_haab_position - haab_position) % 365;
        date[0] += haab_correction;
    }

    std::pair<int, std::string> get_nahual() {
        // Calculate the Tzolk'in day number (1 to 13)
        int nahual_number = (date[0] % 13) + 1;

        // Calculate the Tzolk'in day name (cycles every 20 days)
        std::string nahual_name = nahuales[date[0] % 20];
        return {nahual_number, nahual_name};
    }

    std::pair<int, std::string> get_uinal() {
        // Determine the current Uinal number
        int uinal_number = date[1] + 1;
        std::string uinal_name;
        if (uinal_number <= 18) {
            uinal_name = uinals[uinal_number - 1];
        } else {  // Wayeb' period (the 5 extra days at the end of the Haab' year)
            uinal_number = 19;
            uinal_name = "Wayeb'";
        }
        return {uinal_number, uinal_name};
    }

    std::string to_string() {
        std::ostringstream oss;
        std::reverse(date.begin(), date.end());
        for (int d : date) {
            oss << d << ".";
        }
        std::reverse(date.begin(), date.end());
        auto [nahual_number, nahual_name] = get_nahual();
        auto [uinal_number, uinal_name] = get_uinal();
        oss << nahual_number << " " << nahual_name << " " << uinal_number << " " << uinal_name;
        return oss.str();
    }

private:
    std::vector<int> periods;
    std::vector<int> date;
    std::vector<std::string> nahuales;
    std::vector<std::string> uinals;
};

int main() {
    // Initialize the calendar with the given date
    MayanCalendarCounter calendar(13, 0, 11, 14, 15);

    // Print the current date with the expected format
    std::cout << "Current Mayan date: " << calendar.to_string() << std::endl;

    // Increment by 1 day and print the updated date
    calendar.increment(1);
    std::cout << "Mayan date after 1 day: " << calendar.to_string() << std::endl;

    // Increment by a large number of days
    calendar.increment(1000);
    std::cout
