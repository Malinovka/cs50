-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime scenes on July 28 2020 on chamberlin street
SELECT *
FROM crime_scene_reports
WHERE year = 2020 AND month = 07 AND day = 28 AND street LIKE "Chamberlin%";
--295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Check interviews on the day of
SELECT name, transcript
FROM interviews
WHERE year = 2020 AND month = 07 AND day = 28;
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Check courthouse security between 10:15 and 10:25 and check entrance/exit time for those license plates
SELECT license_plate, hour, minute, activity
FROM courthouse_security_logs
WHERE license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE (
        year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
    )
);
--L93JTIZ | 8 | 18 | entrance
--94KL13X | 8 | 23 | entrance
--322W7JE | 8 | 36 | entrance
--0NTHK55 | 8 | 42 | entrance
--4328GD8 | 9 | 14 | entrance
--5P2BI95 | 9 | 15 | entrance
--6P58WS2 | 9 | 20 | entrance
--G412CB7 | 9 | 28 | entrance
--5P2BI95 | 10 | 16 | exit
--94KL13X | 10 | 18 | exit
--6P58WS2 | 10 | 18 | exit
--4328GD8 | 10 | 19 | exit
--G412CB7 | 10 | 20 | exit
--L93JTIZ | 10 | 21 | exit
--322W7JE | 10 | 23 | exit
--0NTHK55 | 10 | 23 | exit

-- Check transactions to see if any of the above used the fifer street atm that day
SELECT name, people.id, transaction_type, amount
FROM people, atm_transactions, bank_accounts
WHERE (
    year = 2020 AND month = 07 AND day = 28 AND atm_location = "Fifer Street"
    AND atm_transactions.account_number = bank_accounts.account_number
    AND people.id = bank_accounts.person_id
    AND person_id IN (
        SELECT id
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM courthouse_security_logs
            WHERE (
                year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
            )
        )
    )
);
--Ernest | 686048 | withdraw | 50
--Russell | 514354 | withdraw | 35
--Elizabeth | 396669 | withdraw | 20
--Danielle | 467400 | withdraw | 48

-- Check the above peoples phone calls for that day for one less than 60 seconds
SELECT name, caller, receiver, duration
FROM people, phone_calls
WHERE (
    year = 2020 AND month = 07 AND day = 28 AND duration < 60
    AND people.phone_number = phone_calls.caller
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE id IN (
            SELECT people.id
            FROM people, atm_transactions, bank_accounts
            WHERE (
                year = 2020 AND month = 07 AND day = 28 AND atm_location = "Fifer Street"
                AND atm_transactions.account_number = bank_accounts.account_number
                AND people.id = bank_accounts.person_id
                AND person_id IN (
                    SELECT id
                    FROM people
                    WHERE license_plate IN (
                        SELECT license_plate
                        FROM courthouse_security_logs
                        WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
                    )
                )
            )
        )
    )
);
--Ernest | (367) 555-5533 | (375) 555-8161 | 45
--Russell | (770) 555-1861 | (725) 555-3243 | 49

--Who did they call
SELECT name, receiver
FROM people, phone_calls
WHERE (
    year = 2020 AND month = 07 AND day = 28 AND duration < 60
    AND people.phone_number = phone_calls.receiver
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE id IN (
            SELECT people.id
            FROM people, atm_transactions, bank_accounts
            WHERE (
                year = 2020 AND month = 07 AND day = 28 AND atm_location = "Fifer Street"
                AND atm_transactions.account_number = bank_accounts.account_number
                AND people.id = bank_accounts.person_id
                AND person_id IN (
                    SELECT id
                    FROM people
                    WHERE license_plate IN (
                        SELECT license_plate
                        FROM courthouse_security_logs
                        WHERE (
                        year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
                        )
                    )
                )
            )
        )
    )
);
--Berthold | (375) 555-8161
--Philip | (725) 555-3243

--Airports in fiftyville
SELECT *
FROM airports
WHERE city = "Fiftyville";
--8 | CSF | Fiftyville Regional Airport | Fiftyville

-- Earliest flight tomorrow from fiftyville
SELECT hour, minute
FROM flights
WHERE year = 2020 AND month = 07 AND day = 29 AND origin_airport_id = 8
ORDER BY hour, minute;
--8 | 20
--9 | 30
--12 | 15
--15 | 20
--16 | 0

-- Who is on a flight tomorrow
SELECT passport_number, city, hour, minute
FROM passengers, airports, flights
WHERE (
    origin_airport_id = 8 AND year = 2020 AND month = 07 AND day = 29
    AND airports.id = destination_airport_id
    AND flight_id = flights.id
    AND flights.id IN (
        SELECT flight_id
        FROM passengers
        WHERE passport_number IN (
            SELECT passport_number
            FROM people
            WHERE id IN (
                514354, 686048
            )
        )
    )
    AND passport_number IN (
        SELECT passport_number
        FROM people
        WHERE id IN (
            514354, 686048
        )
    )
)
ORDER BY hour, minute;
--5773159633 | London | 8 | 20
--3592750733 | Boston | 16 | 0

SELECT DISTINCT passengers.passport_number, name
FROM passengers, people
WHERE (
    passengers.passport_number = people.passport_number
    AND passengers.passport_number IN (
        SELECT passport_number
        FROM passengers, airports, flights
        WHERE origin_airport_id = 8 AND year = 2020 AND month = 07 AND day = 29
        AND flights.id IN (
            SELECT flight_id
            FROM passengers
            WHERE passport_number IN (
                SELECT passport_number
                FROM people
                WHERE id IN (
                    514354, 686048
                )
            )
        )
        AND airports.id = destination_airport_id
        AND flight_id = flights.id
        AND passport_number IN (
            SELECT passport_number
            FROM people
            WHERE id IN (
                514354, 686048
            )
        )
    )
);
--3592750733 | Russell
--5773159633 | Ernest