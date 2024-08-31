class MayanCalendarCounter:
    def __init__(self, prec=52, baktun=13, katun=0, tun=11, uinal=14, kin=15):
        # Mayan periods in days (1, 20, 360, 7200, 144000, 1872000, 93600000)
        self.periods = [1, 20, 360, 7200, 144000, 1872000, 93600000]
        # Initialize the Mayan date
        self.date = [kin, uinal, tun, katun, baktun, prec, 0]
        # Nahuales (Kin names) and Uinal names
        self.nahuales = ["Imix", "Ik’", "Ak’bal", "K’an", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "K’ib", "Kaban", "Etznab", "Kauak", "Ajau"]
        self.uinals = ["Pop", "Uo ’", "Zip", "Sots", "Tsek", "Xul", "Yaxkin", "Mol", "Ch’en", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "K’ayab", "Kumk’u", "Uayeb"]

# started on:
# Tzolk'in Day: 1 Ben
# Haab' Day: 3 Zip

    def increment(self, days=1):
        """Increment the counter by a certain number of days."""
        for i in range(len(self.periods)):
            self.date[i] += days
            if self.date[i] >= self.periods[i]:
                if i < len(self.periods) - 1:
                    # Carry over to the next period
                    self.date[i + 1] += self.date[i] // self.periods[i]
                    self.date[i] = self.date[i] % self.periods[i]
                else:
                    # If at the highest period, wrap around (overflow)
                    self.date[i] = self.date[i] % self.periods[i]
            else:
                break  # No need to carry over if the current period is within its range

    def adjust_to_start(self):
        """Adjust the initial date to match 1 Ben 3 Zip."""
        # Calculate the total number of days from the Mayan epoch (0.0.0.0.0.0) to the given date
        total_days = (
            self.date[5] * 1872000+ # precession 5 x long count * 1872000
            self.date[4] * 144000 +  # Baktun * 144000 days
            self.date[3] * 7200 +    # Katun * 7200 days
            self.date[2] * 360 +     # Tun * 360 days
            self.date[1] * 20 +      # Uinal * 20 days
            self.date[0]             # Kin * 1 day
        )

        # Determine the position within the Tzolk'in cycle (260 days)
        tzolkin_position = total_days % 260

        # Determine the position within the Haab' cycle (365 days)
        haab_position = total_days % 360

        # Set Tzolk'in to 8 ben
        target_tzolkin_day_number = 1
        target_tzolkin_day_name = "ben'"
        target_tzolkin_position = (self.nahuales.index(target_tzolkin_day_name) + (target_tzolkin_day_number - 1)) % 260

        # Adjust the Tzolk'in offset to start from 8 ben
        self.date[0] = (target_tzolkin_position - tzolkin_position) % 260

        # Set Haab' to 3 zip
        target_haab_day_number = 3
        target_haab_month_name = "zip"
        target_haab_position = (self.uinals.index(target_haab_month_name) * 20 + (target_haab_day_number - 1)) % 365

        # Adjust the Haab' offset to start from 3 zip
        haab_correction = (target_haab_position - haab_position) % 360
        self.date[0] += haab_correction

        # Adjust other periods based on the correction made
        if self.date[0] >= 20:
            self.date[1] += self.date[0] // 20
            self.date[0] = self.date[0] % 20
        if self.date[1] >= 20:
            self.date[2] += self.date[1] // 20
            self.date[1] = self.date[1] %20
        if self.date[2] >= 20:
            self.date[3] += self.date[2] // 20
            self.date[2] = self.date[2] % 20
        if sf.date[3] >= 20:
            self.date[4] += self.date[3] // 20
            self.date[3] = self.date[3] % 20
        if elf.date[4] >= 52:
            self.date[5] += self.date[4] // 52
            self.date[4] = self.date[4] % 52   

def get_nahual(self):
    # Calculate the Tzolk'in day number (1 to 13)
    nahual_day_number = (self.date[0] % 13) + 1  # Coefficient ranges from 1 to 13
    
    # Calculate the Tzolk'in day name (cycles every 20 days)
    nahual_name = self.nahuales[self.date[0] % 20]
    return nahual_number, nahual

def get_uinal(self):
    # Determine the current Uinal number
    if self.date[0] < 360:  # Within the first 18 Uinals (each 20 days long)
        uinal_number = (self.date[0] // 20) + 1
        uinal_name = self.uinals[uinal_number - 1]
    else:  # Wayeb' period (the 5 extra days at the end of the Haab' year)
        uinal_number = 19
        uinal_name = "Wayeb'"
    return uinal_number, uinal

    formatted_date = ".".join(map(str, reversed(self.date[:-1])))  # Exclude the placeholder period 
    nahual_number, nahual = self.get_nahual()
    uinal_number, uinal = self.get_uinal()
    return f"{formatted_date} {nahual_number} {nahual} {uinal_number} {uinal}"


# Initialize the calendar with the given date
calendar = MayanCalendarCounter(13, 0, 11, 14, 15,52)

# Print the current date with the expected format
print(f"The current date: {calendar} (which should be 13.0.11.14.15.52 1 ben 3 zip)")

# Increment by 1 day and print the updated date
calendar.increment(1)
print(f"Mayan date after 1 day: {calendar}")

# Increment by a large number of days
calendar.increment(1000)
print(f"Mayan date after 1000 days: {calendar}")
