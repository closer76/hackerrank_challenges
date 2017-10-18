"""
Solution of Counting Sundays
https://www.hackerrank.com/contests/projecteuler/challenges/euler019
"""

def is_leap_year(year):
    """ retunrs if 'year' is a leap year """
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)

def days_before_beginning_of_year(year):
    """ returns days count between 1900/01/01 to specified year """
    if year <= 1900:
        return 0

    delta = year - 1900
    days = delta * 365
    days += ((delta - 1) // 4 + 1)
    days -= ((delta - 1) // 100 + 1)
    days += ((delta + 299) // 400)

    return days

def days_of_month(year):
    """ returns a list of days of each month in specified year """
    return [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31] \
        if is_leap_year(year) else \
        [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def days_after_1990(year, month, day):
    """ returns days count between 1900/01/01 to specfied date """
    return days_before_beginning_of_year(year) + \
           sum(days_of_month(year)[:(month-1)]) + \
           min(days_of_month(year)[month-1], day)

def increase_month(year, month):
    """ increase month by 1 and adjust year if necessary """
    if month <= 11:
        return year, month + 1
    else:
        return year + 1, 1

def main():
    """ main function """
    test_count = int(input().strip())
    for _ in range(test_count):
        year_b, month_b, day_b = list(map(int, input().strip().split()))
        year_e, month_e, _ = list(map(int, input().strip().split()))
        if day_b != 1:
            year_b, month_b = increase_month(year_b, month_b)
        year_e, month_e = increase_month(year_e, month_e)

        year, month = year_b, month_b
        days_count = days_after_1990(year, month, 1)
        sunday_count = 0
        while year != year_e or month != month_e:
            if days_count % 7 == 0:
                sunday_count += 1
            days_count += days_of_month(year)[month - 1]
            year, month = increase_month(year, month)

        print(sunday_count)

if __name__ == '__main__':
    main()
