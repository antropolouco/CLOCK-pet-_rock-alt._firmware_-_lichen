#include <iostream>
#include <vector>
#include <string>

class MayanCalendarCounter {
private:
    std::vector<int> periods = {1, 20, 360, 7200, 144000, 1872000};
    std::vector<int> date;
    std::vector<std::string> nahuales = {"Imix", "Ik’", "Ak’bal", "K’an", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok",
                                         "Chuen", "Eb", "Ben", "Ix", "Men", "K’ib", "Kaban", "Etznab", "Kauak", "Ajau"};
    std::vector<std::string> uinals = {"Pop", "Uo", "Zip", "Sots", "Tsek", "Xul", "Yaxkin", "Mol", "Ch’en", "Yax", "Sak",
                                       "Keh", "Mak", "Kankin", "Muan", "Pax", "K’ayab", "Kumk’u", "Uayeb"};

    void adjustToStart() {
        int tzolkin_days = 67;  // 8 Men is the 68th position (0-indexed)
        int haab_days = 337;    // 18 Yaxk'in is the 338th position (0-indexed)

        int total_days = date[4] * 144000 + date[3] * 7200 + date[2] * 360 + date[1] * 20 + date[0];

        total_days += haab_days - (total_days % 365);
        total_days += tzolkin_days - (total_days % 260);

        int baktun = total_days / 144000;
        total_days %= 144000;
        int katun = total_days / 7200;
        total_days %= 7200;
        int tun = total_days / 360;
        total_days %= 360;
        int uinal = total_days / 20;
        int kin = total_days % 20;

        date = {kin, uinal, tun, katun, baktun};
    }

public:
    MayanCalendarCounter(int baktun = 13, int katun = 0, int tun = 11, int uinal = 14, int kin = 15)
        : date{kin, uinal, tun, katun, baktun} {
        adjustToStart();
    }

    void increment(int days = 1) {
        for (size_t i = 0; i < periods.size(); ++i) {
            date[i] += days;
            if (date[i] >= periods[i]) {
                if (i < periods.size() - 1) {
                    date[i + 1] += date[i] / periods[i];
                    date[i] %= periods[i];
                } else {
                    date[i] %= periods[i];
                }
            } else {
                break;
            }
        }
    }

    std::pair<int, std::string> getNahual() const {
        int kin_day_number = (date[0] % 13) + 1;  // Nahual number ranges from 1 to 13
        std::string nahual_name = nahuales[date[0] % 20];  // Nahual name cycles every 20 days
        return {kin_day_number, nahual_name};
    }

    std::pair<int, std::string> getUinal() const {
        int haab_day = (date[1] * 20 + date[0]) % 365;
        int uinal_number = (haab_day % 20) + 1;  // Uinal day number ranges from 1 to 20
        std::string uinal_name = uinals[(haab_day / 20) % 19];  // Uinal name cycles every 19 Uinals
        return {uinal_number, uinal_name};
    }

    std::string toString() const {
        std::string formatted_date;
        for (int i = date.size() - 1; i >= 0; --i) {
            formatted_date += std::to_string(date[i]);
            if (i != 0) {
                formatted_date += ".";
            }
        }

        auto nahual = getNahual();
        auto uinal = getUinal();

        return formatted_date + " " + std::to_string(nahual.first) + " " + nahual.second + " " +
               std::to_string(uinal.first) + " " + uinal.second;
    }
};

int main() {
    MayanCalendarCounter calendar(13, 0, 11, 14, 15);

    // Print the current date (which should be 13.0.11.14.15 8 Men 18 Yaxk'in)
    std::cout << "Current Mayan date: " << calendar.toString() << std::endl;

    // Increment by 1 day and print the updated date
    calendar.increment(1);
    std::cout << "Mayan date after 1 day: " << calendar.toString() << std::endl;

    // Increment by a large number of days
    calendar.increment(1000);
    std::cout << "Mayan date after 1000 days: " << calendar.toString() << std::endl;

    return 0;
}
