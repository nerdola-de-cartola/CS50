-- Keep a log of any SQL queries you execute as you solve the mystery.


--First I run this query and save the answer to a text file so I can always see the database schema
.schema


--This query show me more information about the crime
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2020
AND street = "Chamberlin Street";
--The description mention 3 witnesses how have been interviewed
--I should look up for these interviews


--This query shows the interviews related to the crime
SELECT name, transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2020
ORDER BY name;
--Barbara, Eugene, Jose, Raymond and Ruth have been interviewed
--But just Eugene, Raymond and Ruth interviews has related to the crime
--So I must be focused on these people


--Fists let's follow the track given by Eugene
--This query shows the name of people who withdrawn on Fifer Street on July 28, 2020.
--One of them must be the criminal
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE day = 28
AND month = 7
AND year = 2020
AND atm_location = "Fifer Street"
AND transaction_type = "withdraw";


--Second let's follow the track given by Raymond
--This query shows the name of people who made a call on July 28, 2020
--One of them must be the criminal
SELECT name
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE day = 28
AND month = 7
AND year = 2020
AND duration <= 60;


--Third let's follow the track given by Ruth
--This query shows the name of people who left the Courthouse on July 28, 2020 after 10:15AM
--One of them must be the criminal
SELECT people.name
FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = 28
AND month = 7
AND year = 2020
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = "exit";


--This query uses all the information until this point to reduce the crime suspects
SELECT people.name
FROM people
WHERE name IN (
    SELECT name
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
        WHERE day = 28
        AND month = 7
        AND year = 2020
        AND atm_location = "Fifer Street"
        AND transaction_type = "withdraw"
    )
    AND name IN (
        SELECT name
        FROM people
        JOIN phone_calls ON phone_calls.caller = people.phone_number
        WHERE day = 28
        AND month = 7
        AND year = 2020
        AND duration <= 60
    )
    AND name IN (
        SELECT people.name
        FROM people
        JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
        WHERE day = 28
        AND month = 7
        AND year = 2020
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = "exit"
    );
-- The list of suspects it's now just Ernest or Russell


--Let's see if they have traveled on July 29, 2020
SELECT people.name, hour, minute, ap_1.city AS "org_city", ap_2.city AS "dst_city"
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports AS ap_1 ON flights.origin_airport_id = ap_1.id
JOIN airports AS ap_2 ON flights.destination_airport_id = ap_2.id
WHERE flights.year = 2020
AND month = 7
AND day = 29
AND org_city = "Fiftyville"
ORDER BY hour, minute;
--Ernest took the first plane to London and Russell took the last one to Boston
--So it must be Ernest


--Now let's see who Ernest call on July 28, 2020 to find his accomplice
SELECT cal.name, rec.name
FROM phone_calls
JOIN people AS cal ON cal.phone_number = phone_calls.caller
JOIN people AS rec ON rec.phone_number = phone_calls.receiver
WHERE day = 28
AND month = 7
AND year = 2020
AND duration <= 60
AND cal.name = "Ernest";
--Ernest have called Berthold for less than 10 minutes in the day of the crime
--so Berthold is the accomplice