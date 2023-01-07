/*What i know:
 Fiftyville, Humphrey Street, July 28 2021
 The thief stole the duck
 shortly afterwards, took a flight out of town
 with the help of an accomplice

What I have to find:
Who the thief is,
What city the thief escaped to, and
Who the thief’s accomplice is who helped them escape
*/

--to see the database structure
.schema

--checking what general information does the table crime scene reports holds
SELECT * FROM crime_scene_reports;

--cheking reports of criem at the street of the theft
SELECT * FROM crime_scene_reports
WHERE street = "Humphrey Street";

/*
Report id 295 happened is of the CS50 duck theft. Now I know:
happened at 10:15am
happened at Humphrey Street bakery
3 witnesses gave interviews, which transcripts mentioned the Humphrey Street bakery
*/

--looking for interviews from date of theft that mentioned "bakery"
SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND instr(transcript, "bakery") != 0;

/*
Returned 3 interviews, 161 Ruth, 162 Eugene, 163 Raymond. Now I know:
Ruth: beetwen 10:15am and 10:25am thief got into a car at the bakery parking lot and left. look for security footage form the balery parking lot
Eugene: earlier same day thief was walkning by Leggett Street ATM
Raymond: thief called for less than a minute, said planning to take earliest fight out tomorrow, asked for accomplice to buy the ticket
*/

/*
looking for people at the Leggett Street ATM at the date of thief before time of thief, possible suspects
checking schema I found that there isn't a time columm but there is a ammount columm
gonna check if thief said ammount to accomplice and see what else:
table doesn't contain transcript of phone calls conversations, but from I can associate the phone numbers to the people number to the peoples table, assuming that phone number is from thief
people table also have lisence_plate, maybe i can find this at bakery security logs
*/
SELECT caller FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration <= 60;

--looking for lisence plate of car that left bakery parking lot
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15 AND minute <= 25;

--lookinf for people that have phone number and one of the lisence plate listed
--this returned 4 suspects of theft, im gonne check which if their passaports was in th earlier flight the next day of the theft
SELECT passport_number FROM people
WHERE phone_number IN
    (SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60)
AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15 AND minute <= 25);

--check earliest flight at 2021 7 29
SELECT id FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC, minute ASC
LIMIT 1;

--check for passagers of the flight that has the suspected passaports, see if is one of those 4 from people
--this returned 3 suspects, I'm gonna check the origin airport of the flights, I forgot that
SELECT * FROM passengers
WHERE flight_id IN
    (SELECT id FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    ORDER BY hour ASC, minute ASC
    LIMIT 1)
AND passport_number IN
    (SELECT passport_number FROM people
    WHERE phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration <= 60)
    AND license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15 AND minute <= 25));

--looking for id of the fyftyville airport
SELECT id FROM airports
WHERE full_name = "Fiftyville Regional Airport";

--check earliest flight at 2021 7 29 with origin at Fiftyville Regional Airport
--It's the same flight, maybe I can find some information on the destination of the thief to narrow down the possible flights with this origin
--going another path for now and maybe comeback to this later
SELECT * FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
AND origin_airport_id IN
    (SELECT id FROM airports
    WHERE full_name = "Fiftyville Regional Airport")
ORDER BY hour ASC, minute ASC;

--gonna check people with the caller number phone, license plate and made transactions at Leggett Street ATM
--suspecting of id 267 because its the only 50 value transaction (CS50 lol)
SELECT account_number FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street";

--getting id of peole with this account number from bank accounts
SELECT person_id FROM bank_accounts
WHERE account_number IN
    (SELECT account_number FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = "Leggett Street");

--cheking caller of phone_calls with less than a minute that was parked at bakery parkinf lot beetwen 10:15 and 10:25 and made a transaction at Leggett Street ATM all at 2021 7 28
--there are 2 suspects
SELECT passport_number FROM people
WHERE id IN
    (SELECT person_id FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))
AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15 AND minute <= 25)
AND phone_number IN
    (SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60);

--gonna check for these two suspects in flights leaving Fyftyville the morning of 2021 7 29
SELECT passport_number FROM passengers
WHERE flight_id IN
    (SELECT id FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    ORDER BY hour ASC, minute ASC
    LIMIT 1)
AND passport_number IN
    (SELECT passport_number FROM people
    WHERE id IN
        (SELECT person_id FROM bank_accounts
        WHERE account_number IN
            (SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street"))
    AND license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15 AND minute <= 25)
    AND phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration <= 60));

/* FINAL SUSPECT:
made a transaction at an ATM at Leggett Street morning of the theft
made a phone call with less than one minute asking for accomplice to buy ticket
leaved in a car at parking lot of the bakery in as most 10 min after the theft
left fyftyville the earlest flight next morning
id of suspect = 686048
name of suspect = Bruce
*/
SELECT * FROM people
WHERE id IN
    (SELECT person_id FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))
AND phone_number IN
    (SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60)
AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15 AND minute <= 25)
AND passport_number IN
    (SELECT passport_number FROM passengers
    WHERE flight_id IN
        (SELECT id FROM flights
        WHERE year = 2021
        AND month = 7
        AND day = 29
        ORDER BY hour ASC, minute ASC
        LIMIT 1));

--accomplice is the receiver of the call
--suspect made multiple calls?!?
SELECT receiver from phone_calls
WHERE caller IN
        (SELECT phone_number FROM people
        WHERE id IN
        (SELECT person_id FROM bank_accounts
        WHERE account_number IN
            (SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street"))
        AND phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration <= 60)
        AND license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15 AND minute <= 25)
        AND passport_number IN
        (SELECT passport_number FROM passengers
        WHERE flight_id IN
            (SELECT id FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            ORDER BY hour ASC, minute ASC
            LIMIT 1)));

--let's see where Bruce's flight of the next day was heading
SELECT destination_airport_id FROM
flights JOIN passengers ON flights.id = passengers.flight_id
WHERE passengers.passport_number = 5773159633; --Bruce's passport number

-- Bruce headed to New York City
SELECT city FROM airports
WHERE id IN
    (SELECT destination_airport_id FROM
    flights JOIN passengers ON flights.id = passengers.flight_id
    WHERE passengers.passport_number = 5773159633); --Bruce's passport number

/*
Now to find the accomplice, what i know about him:
Bruce called him day of crime
Duration of call was Less than a minute
Bruce asked him to buy the ticket
*/
SELECT receiver FROM phone_calls
WHERE caller IN
    (SELECT phone_number FROM people
    WHERE id = 686048)
AND year = 2021
AND month = 7
AND day = 28
AND duration <= 60;

--accomplice is the receiver of the call
SELECT * FROM people
WHERE phone_number IN
    (SELECT receiver FROM phone_calls
    WHERE caller IN
        (SELECT phone_number FROM people
        WHERE id = 686048)
    AND year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60);